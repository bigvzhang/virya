#pragma once
namespace virya {
namespace experimental {

template <class RealObj>
class unique_ptr{
private:
	RealObj* _content;
public:
	unique_ptr(RealObj* param_content = nullptr) : _content(param_content){}
	unique_ptr(const unique_ptr& o) = delete;
	unique_ptr& operator=(const unique_ptr& o) = delete;
	unique_ptr& operator=(RealObj* v){if(_content) delete _content; _content =v; return *this;}
	~unique_ptr(){ delete(_content); }
	operator RealObj* () { return _content; }
	RealObj* content(){ return _content; }
	RealObj* operator->(){ return _content; }
	void set(RealObj*o){delete(_content);_content = o;}
};


}
}

