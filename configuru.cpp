// https://emilk.github.io/Configuru/html/index.html
#define CONFIGURU_IMPLEMENTATION 1
#define CONFIGURU_VALUE_SEMANTICS 0
#include <configuru.hpp>

  
//#define jsndeletearrayidx(jsna,idx){\\
//	jsn jsntemp=jsn::array();

#if 0
read string
jsn jhist=configuru::parse_string(hist.c_str(),JSON,"nn");;

write file
dump_file("file.json",js,JSON);

read file
js=parse_file("file.json", JSON);

exists
fxsymbs.has_key("EURUSD");


	saveload("fxjusd",fxjusd);
	fxjusdstr= jsn::object();
	///	dbgv(mmc.as_array().size());


	///add
		jsn mmco=jsn::object();;
		mmco["symb"]="teste2";
		mmc.as_array().push_back(mmco);
		dbgv((string)mmc[0]["symb"]);

		///delete index
#endif
