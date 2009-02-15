//
// MessagePack for C++ static resolution routine
//
// Copyright (C) 2008 FURUHASHI Sadayuki
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//
#ifndef MSGPACK_TYPE_ARRAY_HPP__
#define MSGPACK_TYPE_ARRAY_HPP__

#include "msgpack/object.hpp"
#include <vector>

namespace msgpack {


template <typename T>
inline std::vector<T> operator>> (object o, std::vector<T>& v)
{
	if(o.type != type::ARRAY) { throw type_error(); }
	v.resize(o.via.container.size);
	object* p(o.via.container.ptr);
	object* const pend(o.via.container.ptr + o.via.container.size);
	T* it(&v.front());
	for(; p < pend; ++p, ++it) {
		convert(*it, *p);
	}
	return v;
}


template <typename Stream, typename T>
inline packer<Stream>& operator<< (packer<Stream>& o, const std::vector<T>& v)
{
	o.pack_array(v.size());
	for(typename std::vector<T>::const_iterator it(v.begin()), it_end(v.end());
			it != it_end; ++it) {
		pack(*it, o);
	}
	return o;
}


}  // namespace msgpack

#endif /* msgpack/type/array.hpp */

