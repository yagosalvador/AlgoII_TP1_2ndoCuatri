#ifndef QUERY_HPP__
#define QUERY_HPP__

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <limits>

#include "errors.hpp"
#include "utils.hpp"
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

    std::string showId(){return id;}
    size_t showT0(){return t0;}
    size_t showTF(){return tf;}
    bool isBad(){return bad;}
    bool isEmpty(){return empty;}


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

            os << std::setprecision(15) << r.avg << ',' << r.min << ',' << r.max << ',' << r.vol;
            return os;
        }
    };

    friend istream& operator>>(istream& is, Query& c) {
        bool good = false;
        std::string str,id;
        stringstream iss, aux;
        double t0 = 0;
        double tf = 0;
        size_t space_count = 0;
        char ch = 0;

        if( (ch = is.get()) ){
            is.putback(ch);
            getline(is,str);
            iss << str;
            while(ch == ' '){
                ch = iss.get();
                space_count++;
            }

            if(ch == '\r' || ch == '\n'){
                c.empty = true;
                c.bad = false;
                return is;
            }
            if(space_count){
                iss.putback(ch);
                iss.clear();
            }
            getline(iss,id,',');
            if(id.length() == 1){
                iss.clear();
            }
            iss >> t0;
            if(iss.fail()){
                c.bad = true;
                good = true;
                c.empty = false;
                return is;
            }

            getline(iss,str,',');
            aux << str;
            if(aux.fail()){
                c.bad = true;
                good = true;
                c.empty = false;
                return is;
            }

            iss >> tf;
            if( iss.fail() ){                
                c.bad = true;
                good = true;
                c.empty = false;
                return is;
            }
            else{
                if(iss >> ch && isalpha(ch)){
                    c.bad = true;
                    good = true;
                    c.empty = false;
                    return is;
                }
                good = true;
                c.bad = false;

            }
        }
        else if (is.good()) { //read only id
            is.putback(ch);
            good = (getline(is,str,',')) ? true : false;
        }
        if (good == true) {
            if((size_t) t0 != t0)
                c.bad = true;
            if(t0 > 0 && tf < 0){
                tf = t0;
            }
            if(t0 < 0)
                c.bad = true;
            if((size_t)tf != tf)
                t0 = tf;
            if(t0 > tf)
                t0 = tf;
            c.id = id;
            c.t0 = t0;
            c.tf = tf;
            c.empty = false;
        } else {
            is.clear(std::ios::badbit);
            std::cerr << ERROR_MSG_CORRUPTED_DATA << std::endl;
        }

        return is;
    }

    const Query::Response& resolve(Sensores& s){
        static Query::Response r;
        std::string str;
        size_t i=0;
        //double absurd = std::numeric_limits<double>::quiet_NaN();;
        Sensor_data max_aux, min_aux, avg_aux;        

        if(bad == true){
            r.setStatus(BAD_QUERY);
            return r;
        }

        if(s[i].getSize() == 0){
            r.setStatus(NO_DATA);
            return r;
        }

        if(empty == true){
            r.setStatus(EMPTY);
            return r;
        }

        if(t0 == tf){
            r.setStatus(NO_DATA);
            return r;
        }
        if(id == ""){ //no id specified
            for(i=0; i < s.getSize(); i++){
                if(t0 < tf && t0 < s[i].getSize()){                    
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
            if (max_aux.isEmpty() && min_aux.isEmpty() && avg_aux.isEmpty()){
                r.setStatus(NO_DATA);
                return r;
            }
            r.setAvg(avg_aux.getValue()/i);
            r.setMin(min_aux.getValue()/i);
            r.setMax(max_aux.getValue()/i);
            r.setVol(tf - t0);
            r.setStatus(OK);
            return r;
        }
        for(i=0; i < s.getSize(); i++){
            if(s[i].showId() == id){
                if(t0 < tf && t0 < s[i].getSize()){
                    if (tf > s[i].getSize()){
                        tf = s[i].getSize();
                    }
                    avg_aux = s[i].getAvg(t0,tf);
                    min_aux = s[i].getMin(t0,tf);
                    max_aux = s[i].getMax(t0,tf);
                    if (max_aux.isEmpty() && min_aux.isEmpty() && avg_aux.isEmpty())
                        r.setStatus(NO_DATA);
                    else{
                        r.setAvg(avg_aux.getValue());
                        r.setMin(min_aux.getValue());
                        r.setMax(max_aux.getValue());
                        r.setVol(tf - t0);
                        r.setStatus(OK);
                    }
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
