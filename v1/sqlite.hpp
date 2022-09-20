#ifndef SQLITE_HPP_INCLUDED
#define SQLITE_HPP_INCLUDED
 
#include "regular.hpp" 
#include "sqlite3.h" 

struct sqlst{
	sqlite3* db;
	sqlite3_stmt *stmt;
	int pd=0;
	void add();
	void start(string zsql);
	template <typename  T,typename... Params>
	void add(T current,Params... params){
		pd++; 
		bind(current,pd);
		add(params...);
	}
	template <typename... Params>
	sqlst(sqlite3* Db,string zsql, Params... params){ 
		db=Db;		
		start(zsql);
		add(params...); 
	}
	sqlst(sqlite3* Db,string zsql);
	void bind(int x,int id);
	void bind(unsigned int x,int id);
	void bind(double x,int id);
	void bind(float x,int id);
	void bind(string x,int id);
};



#endif // SQLITE_HPP_INCLUDED