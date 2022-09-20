#include "fl_editor.hpp"
#include <FL/fl_draw.H>
#include <FL/fl_ask.H>
#include "stringf.hpp"
#include <unordered_map>

void style_unfinished_cb(int, void*);
void style_update(int pos, int nInserted, int nDeleted, int , const char * , void *cbArg);
//#define FN (Fl_Font)64
#define TS 11// default editor textsize



Fl_Text_Display::Style_Table_Entry  styletable[8];


unordered_map<string,content> files;

Fl_Editor::Fl_Editor(int x,int y,int w, int h) : Fl_Text_Editor(x,y,w, h) {
	Fl::set_fonts();
	//fl_register_images();
	//color(0);


/*
  //Fl::get_system_colors();
lop(i,0,163){
int t; const char *name;
if(name =Fl::get_font_name((Fl_Font)i,&t)){
	dbgv(name,i);getchar();
	if(string(name)=="Liberation Mono"){
dbgv(i);
		//lop(ci,0,8)styletable[ci][1]=(Fl_Font)i;
		break;
	}
}else break;
}
*/

int FN=5;

styletable[0]={ FL_BLACK, FN, TS , 0};// A - Plain
styletable[1]={ FL_DARK_GREEN, FN, TS , 0};
styletable[2]={ FL_DARK_GREEN, FN, TS , 0};
styletable[3]={ FL_BLUE, FN, TS , 0};
styletable[4]={ FL_DARK_RED, FN, TS , 0};
styletable[5]={ FL_DARK_GREEN, FN, TS , 0};
styletable[6]={ FL_DARK_BLUE, FN, TS , 0};
styletable[7]={ FL_BLACK, FN, TS , FL_YELLOW};


//styletable =(Fl_Text_Display::Style_Table_Entry){	// Style table
//		 { FL_BLACK, FN, TS , 0},
//		 { , FN, TS,0 }, // B - Line comments
//		 { , FN, TS,0 }, // C - Block comments
//		 { , FN, TS,0 }, // D - Strings
//		 { , FN, TS,0 }, // E - Directives
//		 { , FN, TS,0 }, // F - Types
//		 { , FN, TS ,0}, // G - Keywords
//		 { , FN, TS , } // H - Highlight
//
//		 };


//	lop(ci,0,8)styletable[ci][1]=(Fl_Font)2;

//dbgv(t,name);
	textbuf = new Fl_Text_Buffer;
	textbuf->tab_distance(2);
	//textfont(FL_HELVETICA);
	style_init();
	highlight_data(stylebuf, styletable, sizeof(styletable) / sizeof(styletable[0]), 'A', style_unfinished_cb, 0);
	buffer(textbuf);
	textbuf->add_modify_callback(style_update,  this);

 	wrap_mode(Fl_Text_Editor::WRAP_AT_PIXEL, 0);

	linenumber_width(17);
	linenumber_size(9);


	//fill(search+0,search+256,0);

}

void Fl_Editor::commentUncommment(int flag){
	string sel=textbuf->selection_text();
	int ip=insert_position();
dbgv(ip,sel);
	//int selsz=ssm(SCI_GETSELTEXT);
	//char buffsel[selsz];
/*
	ssm(SCI_GETSELTEXT, 0, (LPARAM) buffsel);

	int startl=ssm(SCI_GETSELECTIONSTART);
	startl=ssm(SCI_LINEFROMPOSITION,startl);
	int endl=ssm(SCI_GETSELECTIONEND);
	endl=ssm(SCI_LINEFROMPOSITION,endl);

	if(flag==0)
	lop(i,startl,endl+1){
		int li=ssm(SCI_POSITIONFROMLINE,i);
		ssm(SCI_INSERTTEXT,li,(LPARAM) "//");
	}

	if(flag==1)
	lop(i,startl,endl+1){
		int li=ssm(SCI_POSITIONFROMLINE,i);
		int lisz=ssm( SCI_LINELENGTH,i);
		char buffline[lisz];
		ssm(SCI_GETLINE, i, (LPARAM) buffline);
		lop(c,0,lisz){
			if(buffline[c]=='\t' || buffline[c]==' ')continue;
			if(string(buffline+c,2)=="//")
				ssm(SCI_DELETERANGE,li+c,2);
			break;
		}

//SCI_DELETERANGE

//		ssm(SCI_INSERTTEXT,li,"//");
	}

//	SCI_GETSELECTIONEND
//	SCI_LINEFROMPOSITION(int position)
//	SCI_LINEFROMPOSITION(int position)
//	SCI_POSITIONFROMLINE(int line)
*/
};



void Fl_Editor::addText(string txt){
	removeChar(&txt[0], '\r', txt.size());
	string p=textbuf->text();
	textbuf->insert(p.size(),txt.c_str());
	mVScrollBar->value(mVScrollBar->maximum());
	mVScrollBar->do_callback();
	resize(x(), y(), w(), h());
	Fl::check();
}
void Fl_Editor::text(string txt){
	removeChar(&txt[0], '\r', txt.size());
	if(cnt)cnt->modified=0;
	textbuf->text(txt.c_str());
}
string Fl_Editor::text(){
	return textbuf->text();
}
void Fl_Editor::save(string filename){
//return;
	if(filename!="")filenamecurrent=filename;
//dbgv("saved ",filenamecurrent, (cnt==0 || !cnt->modified));
	if(cnt==0 || !cnt->modified)return;
	if(filenamecurrent=="")return;
	if (textbuf->savefile(filenamecurrent.c_str()))
		fl_alert("Error writing to file \'%s\':\n%s.", filenamecurrent.c_str(), strerror(errno)); else{
	if(cnt)cnt->modified=0;
	if(onSave)voidToFunc(onSave,string)(filenamecurrent);
}
}


void Fl_Editor::load(string filename){
	save();//this will always save
	auto got=files.find(filenamecurrent);
	if(got!=files.end()){
		files[filenamecurrent].mTopLineNum=mTopLineNum;
	}
	filenamecurrent=filename;
	got=files.find(filename);
	if(got!=files.end()){
		cnt=&files[filename];
 		textbuf=files[filename].textbuf;
		//mBuffer=textbuf;
		buffer(textbuf);
		stylebuf=files[filename].stylebuf;
		mStyleBuffer=stylebuf;
		highlight_data(stylebuf, styletable, sizeof(styletable) / sizeof(styletable[0]), 'A', style_unfinished_cb, 0);
		scroll(files[filename].mTopLineNum,0);
		return;
	}
	files.emplace(filename,content());
	cnt=&files[filename];
	textbuf = new Fl_Text_Buffer;
	stylebuf = new Fl_Text_Buffer;
	style_init();
	textbuf->tab_distance(2);
		highlight_data(stylebuf, styletable, sizeof(styletable) / sizeof(styletable[0]), 'A', style_unfinished_cb, 0);

	textbuf->add_modify_callback(style_update,  this);
	buffer(textbuf);
	files[filename].textbuf=mBuffer;
	files[filename].stylebuf=mStyleBuffer;


FILE *fp = fopen(filename.c_str(), "rb");
char data[128*1024];
int lenFile = fread(data, 1, sizeof(data), fp);
textbuf->text("");
string t;
while (lenFile > 0) {
  data[lenFile]='\0';
	removeChar(data, '\r', lenFile);
//t=data;
//	subst(t,"\r","");
//t.erase(std::find(t.begin(),t.end(),"\r"));
    textbuf->append(data);
    lenFile = fread(data, 1, sizeof(data), fp);
}
fclose(fp);


// if (textbuf->loadfile(filename.c_str()))
//	fl_alert("Error reading from file \'%s\':\n%s.", filename.c_str(), strerror(errno));
//	else
filenamecurrent=filename;
	resize(x(), y(), w(), h());
  textbuf->call_modify_callbacks();
cnt->modified=0;
}



const char *code_keywords[] = {   "align_union","alignof","and","and_eq","asm","auto","bitand","bitor","bool","break","case","catch","char","class","compl","const","const_cast","constexpr","continue","decltype","default","delete","do","double","dynamic_cast","else","enum","explicit","export","extern","false","final","float","for","friend","goto","if","import","inline","int","int_fast16_t","int_fast32_t","int_fast64_t","int_fast8_t","int_least16_t","int_least32_t","int_least64_t","int_least8_t","int16_t","int32_t","int64_t","int8_t","intmax_t","intptr_t","long","mutable","namespace","new","not","not_eq","nullptr","operator","or","or_eq","override","private","protected","public","register","reinterpret_cast","return","short","signed","size_t","sizeof","static","static_assert","static_cast","struct","switch","template","this","throw","time_t","true","try","typedef","typeid","typename","uint_fast16_t","uint_fast32_t","uint_fast64_t","uint_fast8_t","uint_least16_t","uint_least32_t","uint_least64_t","uint_least8_t","uint16_t","uint32_t","uint64_t","uint8_t","uintmax_t","uintptr_t","union","unsigned","using","virtual","void","volatile","wchar_t","wchar_t","wctrans_t","wctype_t","while","wint_t","xor","xor_eq" };
const char *code_types[] = { "__gnu_cxx","accumulate","add_const","add_cv","add_lvalue_reference","add_pointer","add_reference","add_rvalue_reference","add_volatile","adjacent_difference","adjacent_find","aligned_storage","Alignment","alignment_of","all_of","allocate_shared","allocator","allocator_base","allocator_chunklist","allocator_fixed_size","allocator_newdel","allocator_suballoc","allocator_unbounded","allocator_variable_size","any_of","array","assign","at","atomic_bool","atomic_char","atomic_char16_t","atomic_char32_t","atomic_compare_exchange_strong","atomic_compare_exchange_strong_explicit","atomic_compare_exchange_weak","atomic_compare_exchange_weak_explicit","atomic_exchange","atomic_exchange_explicit","atomic_fetch_add","atomic_fetch_and","atomic_fetch_or","atomic_fetch_sub","atomic_fetch_xor","atomic_int","atomic_int_fast16_t","atomic_int_fast32_t","atomic_int_fast64_t","atomic_int_fast8_t","atomic_int_least16_t","atomic_int_least32_t","atomic_int_least64_t","atomic_int_least8_t","atomic_intmax_t","atomic_intptr_t","atomic_is_lock_free","atomic_llong","atomic_load","atomic_load_explicit","atomic_long","atomic_ptrdiff_t","atomic_schar","atomic_short","atomic_size_t","atomic_ssize_t","atomic_store","atomic_store_explicit","atomic_uchar","atomic_uint","atomic_uint_fast16_t","atomic_uint_fast32_t","atomic_uint_fast64_t","atomic_uint_fast8_t","atomic_uint_least16_t","atomic_uint_least32_t","atomic_uint_least64_t","atomic_uint_least8_t","atomic_uintmax_t","atomic_uintptr_t","atomic_ullong","atomic_ulong","atomic_ushort","atomic_wchar_t","auto_ptr","back","back_insert_iterator","back_item","bad_alloc","bad_function_call","bad_weak_ptr","basic_filebuf","basic_fstream","basic_ifstream","basic_ofstream","basic_regex","basic_streambuf","basic_string","begin","bernoulli_distribution","bidirectional_iterator_tag","binary_function","binary_negate","binary_search","bind","bind1st","bind2nd","binder1st","binder2nd","binomial_distribution","bit_and","bit_or","bit_xor","bitset","boost","cache_chunklist","cache_freelist","cache_suballoc","cauchy_distribution","cbegin","cend","cerr","char_traits","checked_array_iterator","checked_uninitialized_copy","checked_uninitialized_fill_n","chi_squared_distribution","cin","clear","codecvt","codecvt_base","codecvt_byname","codecvt_mode","codecvt_utf16","codecvt_utf8","codecvt_utf8_utf16","collate","collate_byname","common_type","compare_exchange_strong","compare_exchange_weak","complex","condition_variable","conditional","const_iterator","const_mem_fun_ref_t","const_mem_fun_t","const_mem_fun1_ref_t","const_mem_fun1_t","const_pointer_cast","const_reference","const_reverse_iterator","copy","copy_backward","copy_if","copy_n","count","count_if","cout","crbegin","cref","crend","ctype","ctype_base","ctype_byname","decay","declare_no_pointers","declare_reachable","declval","default_delete","default_random_engine","deque","difference_type","discard_block","discard_block_engine","discrete_distribution","divides","domain_error","dynamic_pointer_cast","empty","enable_if","enable_shared_from_this","end","endl","equal","equal_range","equal_to","EqualityComparable","erase","error_category","error_code","error_condition","exception","exponential_distribution","extent","extreme_value_distribution","fetch_add","fetch_and","fetch_or","fetch_sub","fetch_xor","filebuf","fill","fill_n","find","find_end","find_first_not_of","find_first_of","find_if","find_if_not","find_last_not_of","find_last_of","fisher_f_distribution","float_denorm_style","float_round_style","for_each","forward","forward_iterator_tag","forward_list","freelist","front","front_insert_iterator","front_item","fstream","function","gamma_distribution","generate","generate_n","generic_container","generic_iterator","generic_reverse_iterator","generic_value","geometric_distribution","get_deleter","get_pointer_safety","get_temporary_buffer","greater","greater_equal","has_nothrow_assign","has_nothrow_constructor","has_nothrow_copy","has_nothrow_copy_assign","has_nothrow_copy_constructor","has_nothrow_default_constructor","has_trivial_assign","has_trivial_constructor","has_trivial_copy","has_trivial_copy_assign","has_trivial_copy_constructor","has_trivial_default_constructor","has_trivial_destructor","has_virtual_destructor","hash","hash_map","hash_set","ifstream","includes","independent_bits_engine","initializer_list","inner_product","inplace_merge","input_iterator_tag","insert","insert_iterator","integral_constant","invalid_argument","ios_base","iostream","is_abstract","is_arithmetic","is_array","is_base_of","is_bind_expression","is_class","is_compound","is_const","is_constructible","is_convertible","is_empty","is_enum","is_error_code_enum","is_error_condition_enum","is_explicitly_convertible","is_floating_point","is_function","is_fundamental","is_heap","is_heap_until","is_integral","is_literal_type","is_lock_free","is_lvalue_reference","is_member_function_pointer","is_member_object_pointer","is_member_pointer","is_nothrow_constructible","is_object","is_partitioned","is_placeholder","is_pod","is_pointer","is_polymorphic","is_reference","is_rvalue_reference","is_same","is_scalar","is_signed","is_sorted","is_sorted_until","is_standard_layout","is_trivial","is_union","is_unsigned","is_void","is_volatile","istream","istream_iterator","istreambuf_iterator","iter_swap","iterator","iterator_traits","knuth_b","length_error","less","less_equal","LessThanComparable","lexicographical_compare","linear_congruential","linear_congruential_engine","list","locale","logic_error","logical_and","logical_not","logical_or","lognormal_distribution","lower_bound","make_checked_array_iterator","make_heap","make_shared","make_signed","make_unsigned","map","match_results","max","max_element","max_fixed_size","max_none","max_unbounded","max_variable_size","mem_fn","mem_fun","mem_fun_ref","mem_fun_ref_t","mem_fun_t","mem_fun1_ref_t","mem_fun1_t","merge","mersenne_twister","mersenne_twister_engine","messages","messages_base","messages_byname","min","min_element","minmax","minmax_element","minstd_rand","minstd_rand0","minus","mismatch","modulus","money_base","money_get","money_put","moneypunct","moneypunct_byname","move","move_backward","move_iterator","mt19937","mt19937_64","multimap","multiplies","multiset","negate","negative_binomial_distribution","new_handler","next_permutation","none_of","normal_distribution","not_equal_to","not1","not2","nothrow","nothrow_t","npos","nth_element","num_get","num_put","numeric_limits","numpunct","numpunct_byname","ofstream","ostream_iterator","ostreambuf_iterator","out_of_range","output_iterator_tag","overflow_error","owner_less","pair","partial_sort","partial_sort_copy","partial_sum","partition","partition_copy","partition_point","piecewise_constant_distribution","piecewise_linear_distribution","plus","pointer_safety","pointer_to_binary_function","pointer_to_unary_function","poisson_distribution","pop_back","pop_front","pop_heap","prev_permutation","priority_queue","ptr_fun","push_back","push_front","push_heap","queue","random_access_iterator_tag","random_device","random_shuffle","range_error","rank","ranlux_base_01","ranlux24","ranlux24_base","ranlux3","ranlux3_01","ranlux4","ranlux4_01","ranlux48","ranlux48_base","ranlux64_base_01","ratio","ratio_add","ratio_divide","ratio_multiply","ratio_subtract","raw_storage_iterator","rbegin","rdbuf","ref","reference","reference_wrapper","regex","regex_constants","regex_error","regex_iterator","regex_token_iterator","regex_traits","remove","remove_all_extents","remove_const","remove_copy","remove_copy_if","remove_cv","remove_extent","remove_if","remove_pointer","remove_reference","remove_volatile","rend","replace","replace_copy","replace_copy_if","replace_if","requires","resize","result_of","return_temporary_buffer","reverse","reverse_copy","reverse_iterator","rotate","rotate_copy","rts_alloc","runtime_error","search","search_n","seed_seq","set","set_difference","set_intersection","set_new_handler","set_symmetric_difference","set_union","setprecision","setw","shared_ptr","shuffle_order_engine","size","size_type","sort","sort_heap","stable_partition","stable_sort","stack","static_pointer_cast","std","streambuf","string","stringstream","student_t_distribution","sub_match","substr","subtract_with_carry","subtract_with_carry_01","subtract_with_carry_engine","swap","swap_ranges","sync_none","sync_per_container","sync_per_thread","sync_shared","system_error","time_base","time_get","time_get_byname","time_put","time_put_byname","to_array","to_string","tr1","transform","tuple","tuple_element","tuple_size","type_info","uchar","uint","ullong","ulong","unary_function","unary_negate","unchecked_uninitialized_copy","unchecked_uninitialized_fill_n","undeclare_no_pointers","undeclare_reachable","underflow_error","uniform_int","uniform_int_distribution","uniform_real","uniform_real_distribution","uninitialized_copy","uninitialized_copy_n","uninitialized_fill","uninitialized_fill_n","unique","unique_copy","unique_ptr","unordered_map","unordered_multimap","unordered_multiset","unordered_set","upper_bound","ushort","valarray","value_type","variate_generator","vbool","vector","vfloat","vint","vshort","vstring","vvbool","vvfloat","vvint","vvshort","vvstring","vvvbool","vvvfloat","vvvint","vvvshort","vvvstring","wcerr","wcin","wcout","weak_ptr","weibull_distribution","wfilebuf","wfstream","wifstream","wiostream","wistream","wofstream","wregex","xor_combine" };


extern "C" {
  int compare_keywords(const void *a,  const void *b) {
 //dbgv(*((const char **)b));//,*((const char **)b) );
    return (strcmp(*((const char **)a), *((const char **)b)));
  }
}

void style_parse(const char *text, char *style, int  length) {
	dbgv("sparse");
  char	     current;
  int	     col;
  int	     last;
  char	     buf[255],
             *bufptr;
  const char *temp;

  // Style letters:
  //
  // A - Plain
  // B - Line comments
  // C - Block comments
  // D - Strings
  // E - Directives
  // F - Types
  // G - Keywords

  for (current = *style, col = 0, last = 0; length > 0; length --, text ++) {
    if (current == 'B' || current == 'F' || current == 'G') current = 'A';
    if (current == 'A') {
      // Check for directives, comments, strings, and keywords...
      if (col == 0 && *text == '#') {
        // Set style to directive
        current = 'E';
      } else if (strncmp(text, "//", 2) == 0) {
        current = 'B';
	for (; length > 0 && *text != '\n'; length --, text ++)  *style++ = 'B';

        if (length == 0) break;
      } else if (strncmp(text, "/*", 2) == 0) {
        current = 'C';
      } else if (strncmp(text, "\\\"", 2) == 0) {
        // Quoted quote...
	*style++ = current;
	*style++ = current;
	text ++;
	length --;
	col += 2;
	continue;
      } else if (*text == '\"') {
        current = 'D';
      } else if (!last && (islower(*text) || *text == '_')) {
        // Might be a keyword...
	for (temp = text, bufptr = buf;
	     (islower(*temp) || *temp == '_') && bufptr < (buf + sizeof(buf) - 1);
	     *bufptr++ = *temp++);

        if (!islower(*temp) && *temp != '_') {
	  *bufptr = '\0';

          bufptr = buf;
//dbgv(cco);
	  if (bsearch(&bufptr, code_types, sizeof(code_types) / sizeof(code_types[0]), sizeof(code_types[0]), compare_keywords)) {
	    while (text < temp) {
	      *style++ = 'F';
	      text ++;
	      length --;
	      col ++;
	    }

	    text --;
	    length ++;
	    last = 1;
	    continue;
	  } else if (bsearch(&bufptr, code_keywords,
	                     sizeof(code_keywords) / sizeof(code_keywords[0]),
		             sizeof(code_keywords[0]), compare_keywords)) {
	     while (text < temp) {

	      *style++ = 'G';
	      text ++;
	      length --;
	      col ++;
	    }

	    text --;
	    length ++;
	    last = 1;
	    continue;
	  }
	}
      }
    } else if (current == 'C' && strncmp(text, "*/", 2) == 0) {
      // Close a C comment...
      *style++ = current;
      *style++ = current;
      text ++;
      length --;
      current = 'A';
      col += 2;
      continue;
    } else if (current == 'D') {
      // Continuing in string...
      if (strncmp(text, "\\\"", 2) == 0) {
        // Quoted end quote...
	*style++ = current;
	*style++ = current;
	text ++;
	length --;
	col += 2;
	continue;
      } else if (*text == '\"') {
        // End quote...
	*style++ = current;
	col ++;
	current = 'A';
	continue;
      }
    }

    // Copy style info...
    if (current == 'A' && (*text == '{' || *text == '}')) *style++ = 'G';
    else *style++ = current;
    col ++;

    last = isalnum(*text) || *text == '_' || *text == '.';

    if (*text == '\n') {
      // Reset column and possibly reset the style
      col = 0;
      if (current == 'B' || current == 'E') current = 'A';
    }
  }
	dbgv("sparsend");
}

#define freee(thing) {if(thing){free(thing);thing=0; }}

void Fl_Editor::style_init(void) {
 char *style = new char[textbuf->length() + 1];
 char *text = textbuf->text();
 memset(style, 'A', textbuf->length());
 style[textbuf->length()] = '\0';
 if (!stylebuf) stylebuf = new Fl_Text_Buffer(textbuf->length());
 style_parse(text, style, textbuf->length());
 stylebuf->text(style);
 delete[] style;
 freee(text)
}
void style_update(int pos, int nInserted, int nDeleted, int , const char * , void *cbArg) {
	dbgv("sparseu");
	int	start,				// Start of text
	end;				// End of text
 char	last,				// Last style on line
	*style,				// Style data
	*text;				// Text data
Fl_Text_Buffer  *stylebuf=((Fl_Editor  *)cbArg)->stylebuf;
Fl_Text_Buffer  *textbuf=((Fl_Editor  *)cbArg)->textbuf;
Fl_Editor  *editor=((Fl_Editor  *)cbArg);
//editor->needrecount=1;
	//editor->highlightsel();

	if (nInserted || nDeleted  ){
		if (editor->cnt)
			editor->cnt->modified = 1;
		if( editor->onUpdate)
			voidToFunc(editor->onUpdate)();
	}
if(editor->cnt)
dbgv(editor->filenamecurrent, editor->cnt->modified , editor->onUpdate==0);

    //editor->modified=1;
 // If this is just a selection change, just unselect the style buffer...
 if (nInserted == 0 && nDeleted == 0) {
 stylebuf->unselect();
 return;
 }

 // Track changes in the text buffer...
 if (nInserted > 0) {
 // Insert characters into the style buffer...
 style = new char[nInserted + 1];
 memset(style, 'A', nInserted);
 style[nInserted] = '\0';

 stylebuf->replace(pos, pos + nDeleted, style);
 //delete[] style;
	freee(style);
 } else {
 // Just delete characters in the style buffer...
 stylebuf->remove(pos, pos + nDeleted);
 }

 // Select the area that was just updated to avoid unnecessary
 // callbacks...
 stylebuf->select(pos, pos + nInserted - nDeleted);

 // Re-parse the changed region; we do this by parsing from the
 // beginning of the previous line of the changed region to the end of
 // the line of the changed region... Then we check the last
 // style character and keep updating if we have a multi-line
 // comment character...
 start = textbuf->line_start(pos);
// if (start > 0) start = textbuf->line_start(start - 1);
 end = textbuf->line_end(pos + nInserted);
 text = textbuf->text_range(start, end);
 style = stylebuf->text_range(start, end);
 if (start==end)
 last = 0;
 else
 last = style[end - start - 1];

// printf("start = %d, end = %d, text = \"%s\", style = \"%s\", last='%c'...\n",
// start, end, text, style, last);

 style_parse(text, style, end - start);
// printf("new style = \"%s\", new last='%c'...\n",
// style, style[end - start - 1]);
 stylebuf->replace(start, end, style);
 editor->redisplay_range(start, end);

 if (start==end || last != style[end - start - 1]) {
// printf("Recalculate the rest of the buffer style\n");
 // Either the user deleted some text, or the last character
 // on the line changed styles, so reparse the
 // remainder of the buffer...
 freee(text);
 freee(style);

 end = textbuf->length();
 text = textbuf->text_range(start, end);
 style = stylebuf->text_range(start, end);
 style_parse(text, style, end - start);
 stylebuf->replace(start, end, style);
 editor->redisplay_range(start, end);
 }

 freee(text);
 freee(style);
	dbgv("sparseuend");
}

void style_unfinished_cb(int, void*) {
}

void Fl_Editor::find_cb() {
  const char *val;
	string sel=textbuf->selection_text();
	if (sel != "")
		search=sel;
  val = fl_input("Search String:", search.c_str());
  if (val != NULL) {
    // User entered a string - go find it!
		search=val;
    //strcpy(search, val);
    find2_cb( );
  }
}

void Fl_Editor::find2_cb() {
  if (search == "") {
    find_cb( );
    return;
  }

  int pos = insert_position();
  int found = textbuf->search_forward(pos, search.c_str(), &pos);
  if (found) {
    textbuf->select(pos, pos+strlen(search.c_str()));
    insert_position(pos+search.size());
    show_insert_position();
		int ln=count_lines(0,pos,1);
		scroll (ln,0);
  }
  else fl_alert("No occurrences of \'%s\' found!", search.c_str());
}

void Fl_Editor::highlightsel(){
	string search=textbuf->selection_text();
	if(search=="" && highsp.size()==0)return;

	int len=search.size();
  int pos = 0;
  int found;
	char *text = textbuf->text();
	char *st = stylebuf->text();
	if(search!=""){
		char* style = new char[len + 1];
		memset(style, 'H', len);
 		style[len] = '\0';
		highsp.push_back(len);
  	while(found = textbuf->search_forward(pos, search.c_str(), &pos)) {
			highsp.push_back(pos);
			highsp.push_back((int)st[pos]);
			stylebuf->replace(pos, pos + len,style);
			pos++;
  	}
		freee(style);
	}else if(highsp.size()>0){
		len=highsp[0];
		char* style = new char[len + 1];
		for(int i=1;i<highsp.size();i+=2){
			memset(style,(char)highsp[i+1], len);
 			style[len] = '\0';
			stylebuf->replace(highsp[i],highsp[i]+len,style);
		}
		highsp.clear();
		freee(style);
	}
}

int Fl_Editor::handle(int e){
	int ret=Fl_Text_Editor::handle(e);

	if(e==FL_KEYDOWN &&  Fl::event_state() ==FL_CTRL && Fl::event_key()==102) find_cb();

	if(e==FL_KEYDOWN &&   Fl::event_key()==65472) find2_cb();

	if(e==FL_PUSH){
		if(onFocus)voidToFunc(onFocus)();
 		}
	if(e==FL_PUSH ){
		dbgv(textbuf->selection_text());
		highlightsel();
	}

/*

if ((e==FL_PUSH && Fl::event_button()==FL_RIGHT_MOUSE  ) || (e==FL_KEYDOWN && Fl::event_key()==FL_Alt_L ) ) {
Fl_Menu_Item rclick_menu[] = {
 {"Search",FL_ALT+'f', [&](Fl_Widget*,void*v){((Fl_Editor*)v)->find_cb(); }, this},
 {"Search next",FL_ALT+'s', [&](Fl_Widget*,void*v){((Fl_Editor*)v)->find2_cb(); }, this},
		 {0}};
const Fl_Menu_Item *m = rclick_menu->popup(Fl::event_x(), Fl::event_y(), 0, 0, 0);
if ( m ) m->do_callback(0, m->user_data());
}
*/


	return ret;
}
#define FILL_MASK         0x0100
#define SECONDARY_MASK    0x0200
#define PRIMARY_MASK      0x0400
#define HIGHLIGHT_MASK    0x0800
#define BG_ONLY_MASK      0x1000
#define TEXT_ONLY_MASK    0x2000
#define STYLE_LOOKUP_MASK   0xff
void Fl_Editor::draw_string(int style, int X, int Y, int toX, const char *string, int nChars) const {

  IS_UTF8_ALIGNED(string)

  const Style_Table_Entry * styleRec;

  /* Draw blank area rather than text, if that was the request */
  if ( style & FILL_MASK ) {
    if (style & TEXT_ONLY_MASK) return;
    clear_rect( style, X, Y, toX - X, mMaxsize );
    return;
  }
  /* Set font, color, and gc depending on style.  For normal text, GCs
   for normal drawing, or drawing within a Fl_Text_Selection or highlight are
   pre-allocated and pre-configured.  For syntax highlighting, GCs are
   configured here, on the fly. */

  Fl_Font font = textfont();
  int fsize = textsize();
  Fl_Color foreground;
  Fl_Color background;

	Fl_Color bgcor=color(); //background color from Style_Table_Entry

  if ( style & STYLE_LOOKUP_MASK ) {
    int si = (style & STYLE_LOOKUP_MASK) - 'A';
    if (si < 0) si = 0;
    else if (si >= mNStyles) si = mNStyles - 1;

    styleRec = mStyleTable  + si;
    font  = styleRec->font;
    fsize = styleRec->size;
	bgcor=styleRec->attr?styleRec->attr:color(); //background color from Style_Table_Entry

    if (style & PRIMARY_MASK) {
      if (Fl::focus() == (Fl_Widget*)this) {
#ifdef __APPLE__
	if (Fl::compose_state) background = color();// Mac OS: underline marked text
	else
#endif
	background = selection_color();
	}
      else background = fl_color_average(bgcor, selection_color(), 0.4f);
    } else if (style & HIGHLIGHT_MASK) {
      if (Fl::focus() == (Fl_Widget*)this) background = fl_color_average(bgcor, selection_color(), 0.5f);
      else background = fl_color_average(bgcor, selection_color(), 0.6f);
    } else background = bgcor;
    foreground = (style & PRIMARY_MASK) ? fl_contrast(bgcor, background) : styleRec->color;
  } else if (style & PRIMARY_MASK) {
    if (Fl::focus() == (Fl_Widget*)this) background = selection_color();
    else background = fl_color_average(bgcor, selection_color(), 0.4f);
    foreground = fl_contrast(textcolor(), background);
  } else if (style & HIGHLIGHT_MASK) {
    if (Fl::focus() == (Fl_Widget*)this) background = fl_color_average(bgcor, selection_color(), 0.5f);
    else background = fl_color_average(bgcor, selection_color(), 0.6f);
    foreground = fl_contrast(textcolor(), background);
  } else {
    foreground = textcolor();
    background = bgcor;//color();
  }

  if ( !active_r() ) {
    foreground = fl_inactive(foreground);
    background = fl_inactive(background);
  }

  if (!(style & TEXT_ONLY_MASK)) {
    fl_color( background );
    fl_rectf( X, Y, toX - X, mMaxsize );
  }
  if (!(style & BG_ONLY_MASK)) {
    fl_color( foreground );
    fl_font( font, fsize );
#if !(defined(__APPLE__) || defined(WIN32)) && USE_XFT
    // makes sure antialiased Ã„Ã–Ãœ do not leak on line above
    fl_push_clip(X, Y, toX - X, mMaxsize);
#endif
    fl_draw( string, nChars, X, Y + mMaxsize - fl_descent());
#ifdef __APPLE__ // Mac OS: underline marked (= selected + Fl::compose_state != 0) text
    if (Fl::compose_state && (style & PRIMARY_MASK)) {
      fl_color( fl_color_average(foreground, background, 0.6) );
      fl_line(X, Y + mMaxsize - 1, X + fl_width(string, nChars), Y + mMaxsize - 1);
    }
#endif
#if !(defined(__APPLE__) || defined(WIN32)) && USE_XFT
    fl_pop_clip();
#endif
  }

  // CET - FIXME
  /* If any space around the character remains unfilled (due to use of
   different sized fonts for highlighting), fill in above or below
   to erase previously drawn characters */
  /*
   if (fs->ascent < mAscent)
   clear_rect( style, X, Y, toX - X, mAscent - fs->ascent);
   if (fs->descent < mDescent)
   clear_rect( style, X, Y + mAscent + fs->descent, toX - x,
   mDescent - fs->descent);
   */
  /* Underline if style is secondary Fl_Text_Selection */

  /*
   if (style & SECONDARY_MASK)
   XDrawLine(XtDisplay(mW), XtWindow(mW), gc, x,
   y + mAscent, toX - 1, Y + fs->ascent);
   */
}
