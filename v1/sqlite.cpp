 

#include "sqlite.hpp"
 
 
void sqlst::add(){
sqlite3_step(stmt);
sqlite3_reset(stmt); 
sqlite3_finalize(stmt);
sqlite3_exec(db, "COMMIT TRANSACTION", 0, 0, 0);
}
void sqlst::start(string zsql){
sqlite3_exec(db, "BEGIN EXCLUSIVE TRANSACTION", 0,0,0);
sqlite3_prepare_v2(db,  zsql.c_str() , -1, &stmt, NULL);	

}

sqlst::sqlst(sqlite3* Db,string zsql){ 
db=Db;
start(zsql);
add();
}

void sqlst::bind(int x,int id){sqlite3_bind_int(stmt, id, x);}
void sqlst::bind(unsigned int x,int id){sqlite3_bind_int(stmt, id, x);}
void sqlst::bind(double x,int id){sqlite3_bind_double(stmt, id, x);}
void sqlst::bind(float x,int id){sqlite3_bind_double(stmt, id, x);}
void sqlst::bind(string x,int id){sqlite3_bind_text(stmt, id, x.c_str(),x.size(),0);}



//struct sqlst{
//	sqlite3* db;
//    sqlite3_stmt *stmt;
//		int pd=0;
//    void add(){ 
//			sqlite3_step(stmt);
//			sqlite3_reset(stmt);
//			sqlite3_finalize(stmt);
//			sqlite3_exec(db, "COMMIT TRANSACTION", 0, 0, 0);
//}
//	void start(char* zsql){
//        sqlite3_exec(db, "BEGIN EXCLUSIVE TRANSACTION", 0,0,0);
//        sqlite3_prepare_v2(db,  zsql , -1, &stmt, NULL);	
//
//	}
//    template <typename  T,typename... Params>
//    void add(T current,Params... params){
//			pd++; 
//			bind(current,pd);
//			add(params...);
//}
//    template <typename... Params>
//    sqlst(sqlite3* Db,char* zsql, Params... params){ 
//				db=Db;		
//				start(zsql);
//				add(params...); 
//		}
//		sqlst(sqlite3* Db,char* zsql){ 
//				db=Db;
//				start(zsql);
//				add();
//    }
//    void bind(int x,int id){sqlite3_bind_int(stmt, id, x);}
//    void bind(unsigned int x,int id){sqlite3_bind_int(stmt, id, x);}
//    void bind(double x,int id){sqlite3_bind_double(stmt, id, x);}
//    void bind(float x,int id){sqlite3_bind_double(stmt, id, x);}
//    void bind(string x,int id){sqlite3_bind_text(stmt, id, x.c_str(),x.size(),0);}
//};
 