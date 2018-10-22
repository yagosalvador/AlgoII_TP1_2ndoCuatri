#ifndef QUERY_HPP__
#define QUERY_HPP__

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <limits>

#include "errors.hpp"
#include "sensors.hpp"

typedef enum {
    OK = 0,
    UNKNOWN_ID = 1,
    BAD_QUERY = 2,
    NO_DATA = 3,
    EMPTY = 4
} status_t;

class Query{
  private:
    std::string id;
    size_t t0;
    size_t tf;
    bool bad;
    bool empty;

  public:
    Query(){
        id = "";
        t0 = 0;
        tf = 0;
        bad = false;
        empty = false;
    }

    ~Query(){};

    Query(std::string s, size_t a, size_t b){
        id = s;
        t0 = a;
        tf = b;
    }

    Query(const Query& q){
      id = q.id;
      t0 = q.t0;
      tf = q.tf;
    }

    friend std::ostream& operator<<(std::ostream& os, Query q){
        os << q.id << ',' << q.t0 << ',' << q.tf;
        return os;
    }

    Query(std::string& s){
        stringstream ss;

        ss << s;
        ss >> id;
        ss >> t0;
        ss >> tf;
    }

    Query(std::stringstream ss){
        ss >> id;
        ss >> t0;
        ss >> tf;
    }

    class Response{ //Class nested. Use only for query response
      private:
        double avg, min, max;
        size_t vol;
        status_t status; 

      public:
        Response (){
            avg = min = max = 0;
            vol = 0;
            status = BAD_QUERY;
        }

        std::string toString() const{
            return status_dict[status];
        }

        ~Response(){}

        void setMax(const double& max2){max = max2;}

        void setMin(const double& min2){min = min2;}

        void setAvg(const double& avg2){avg = avg2;}

        void setVol(const size_t& vol2){vol = vol2;}

        void setStatus(const status_t& status2){status = status2;}



        friend std::ostream& operator<<(std::ostream& os, const Response& r){
            if (r.status != OK){
                os << r.toString();
                return os;
            }

            os << r.avg << ',' << r.min << ',' << r.max << ',' << r.vol;
            return os;
        }
    };

    friend istream& operator>>(istream& is, Query& c) {
        bool good = true;
        std::string str;
        size_t t0 = 0;
        size_t tf = 0;
        char ch = 0;
        /*static int i=0;

        while(i != 2){
            is.get(ch);
            std::cout << ch;
            is.get(ch);
            std::cout << ch << "hola";
            i++;
        }*/



        if (is >> ch) {
            is.putback(ch);
            getline(is,str,',');
            if( is >> ch && isalpha(ch) ){
                is.clear(std::ios::goodbit);
                c.bad = true;
                good = true;
                getline(is,str);//as bad is true, get line to skip the rest of the line
            }
            else if( is.putback(ch) && 
                is >> t0 &&
                is >> ch && ch == ',') {
                if( is >> ch && isalpha(ch)){
                    is.clear(std::ios::goodbit);
                    c.bad = true;
                    good = true;
                }
                else{
                    is.putback(ch);
                    is >> tf;
                    good = true;
                    c.bad = false;
                }
            }
            else
                good = false;
        } else if (is.good()) { //read only id
            is.putback(ch);
            good = (getline(is,str,',')) ? true : false;
        }

        if (good == true) {
            c.id = str;
            c.t0 = t0;
            c.tf = tf;
        } else {
            is.clear(std::ios::badbit);
            std::cerr << ERROR_MSG_CORRUPTED_DATA << std::endl;
        }

        return is;
    }

    const Query::Response& resolve(Sensores& s){
        static Query::Response r;
        std::string str;
        size_t i;
        double absurd = std::numeric_limits<double>::quiet_NaN();;
        double max_aux = absurd, min_aux = absurd, avg_aux = absurd;

        if(bad == true){
            r.setStatus(BAD_QUERY);
            return r;
        }

        if(empty == true){
            r.setStatus(EMPTY);
            return r;
        }
        if(id == ""){ //no id specified
            for(i=0; i < s.getSize(); i++){
                if(t0 <= tf && t0 <= s[i].getSize()){
                    if (tf > s[i].getSize())
                      tf = s[i].getSize();
                    if(i == 0){
                        max_aux = s[i].getMax(t0,tf);
                        min_aux = s[i].getMin(t0,tf);
                        avg_aux = s[i].getAvg(t0,tf);
                    }
                    else {
                        max_aux += s[i].getMax(t0,tf);
                        min_aux += s[i].getMin(t0,tf);
                        avg_aux += s[i].getAvg(t0,tf);
                    }
                }
            }
            if (max_aux == absurd && min_aux == absurd && avg_aux == absurd){
                r.setStatus(NO_DATA);
                return r;
            }
            r.setAvg(avg_aux/i);
            r.setMin(min_aux/i);
            r.setMax(max_aux/i);
            r.setVol(tf - t0);
            r.setStatus(OK);
            return r;
        }

        for(i=0; i < s.getSize(); i++){
            if(s[i].showId() == id){
                if(t0 <= tf && t0 <= s[i].getSize()){
                    if (tf > s[i].getSize())
                      tf = s[i].getSize();
                    r.setAvg(s[i].getAvg(t0,tf));
                    r.setMin(s[i].getMin(t0,tf));
                    r.setMax(s[i].getMax(t0,tf));
                    r.setVol(s[i].getDataVol(t0,tf));
                    r.setStatus(OK);
                    return r;
                }
                r.setStatus(NO_DATA);
                return r;
            }
        }

        r.setStatus(UNKNOWN_ID);
        return r;

    }
};

#endif
