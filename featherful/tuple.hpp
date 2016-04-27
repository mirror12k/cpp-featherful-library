
#pragma once

namespace featherful
{

template <typename T1=void, typename T2=void, typename T3=void, typename T4=void>
class tuple
{
public:
	tuple(T1 v1, T2 v2, T3 v3, T4 v4);

	T1 first() const;
	T2 second() const;
	T3 third() const;
	T4 fourth() const;

	T1 arg0() const;
	T2 arg1() const;
	T3 arg2() const;
	T4 arg3() const;

private:

	const T1 v1;
	const T2 v2;
	const T3 v3;
	const T4 v4;

};

template <typename T1, typename T2, typename T3, typename T4>
tuple<T1, T2, T3, T4>::tuple(T1 v1, T2 v2, T3 v3, T4 v4)
: v1(v1), v2(v2), v3(v3), v4(v4)
{}

template <typename T1, typename T2, typename T3, typename T4>
T1 tuple<T1, T2, T3, T4>::first() const
{
	return this->v1;
}
template <typename T1, typename T2, typename T3, typename T4>
T2 tuple<T1, T2, T3, T4>::second() const
{
	return this->v2;
}
template <typename T1, typename T2, typename T3, typename T4>
T3 tuple<T1, T2, T3, T4>::third() const
{
	return this->v3;
}
template <typename T1, typename T2, typename T3, typename T4>
T4 tuple<T1, T2, T3, T4>::fourth() const
{
	return this->v4;
}
template <typename T1, typename T2, typename T3, typename T4>
T1 tuple<T1, T2, T3, T4>::arg0() const
{
	return this->v1;
}
template <typename T1, typename T2, typename T3, typename T4>
T2 tuple<T1, T2, T3, T4>::arg1() const
{
	return this->v2;
}
template <typename T1, typename T2, typename T3, typename T4>
T3 tuple<T1, T2, T3, T4>::arg2() const
{
	return this->v3;
}
template <typename T1, typename T2, typename T3, typename T4>
T4 tuple<T1, T2, T3, T4>::arg3() const
{
	return this->v4;
}




template <typename T1, typename T2, typename T3>
class tuple<T1, T2, T3, void>
{
public:
	tuple(T1 v1, T2 v2, T3 v3);

	T1 first() const;
	T2 second() const;
	T3 third() const;

	T1 arg0() const;
	T2 arg1() const;
	T3 arg2() const;

private:

	const T1 v1;
	const T2 v2;
	const T3 v3;

};

template <typename T1, typename T2, typename T3>
tuple<T1, T2, T3, void>::tuple(T1 v1, T2 v2, T3 v3)
: v1(v1), v2(v2), v3(v3)
{}

template <typename T1, typename T2, typename T3>
T1 tuple<T1, T2, T3, void>::first() const
{
	return this->v1;
}
template <typename T1, typename T2, typename T3>
T2 tuple<T1, T2, T3, void>::second() const
{
	return this->v2;
}
template <typename T1, typename T2, typename T3>
T3 tuple<T1, T2, T3, void>::third() const
{
	return this->v3;
}
template <typename T1, typename T2, typename T3>
T1 tuple<T1, T2, T3, void>::arg0() const
{
	return this->v1;
}
template <typename T1, typename T2, typename T3>
T2 tuple<T1, T2, T3, void>::arg1() const
{
	return this->v2;
}
template <typename T1, typename T2, typename T3>
T3 tuple<T1, T2, T3, void>::arg2() const
{
	return this->v3;
}




template <typename T1, typename T2>
class tuple<T1, T2, void, void>
{
public:
	tuple(T1 v1, T2 v2);

	T1 first() const;
	T2 second() const;

	T1 arg0() const;
	T2 arg1() const;

private:

	const T1 v1;
	const T2 v2;

};

template <typename T1, typename T2>
tuple<T1, T2, void, void>::tuple(T1 v1, T2 v2)
: v1(v1), v2(v2)
{}

template <typename T1, typename T2>
T1 tuple<T1, T2, void, void>::first() const
{
	return this->v1;
}
template <typename T1, typename T2>
T2 tuple<T1, T2, void, void>::second() const
{
	return this->v2;
}
template <typename T1, typename T2>
T1 tuple<T1, T2, void, void>::arg0() const
{
	return this->v1;
}
template <typename T1, typename T2>
T2 tuple<T1, T2, void, void>::arg1() const
{
	return this->v2;
}




template <typename T1>
class tuple<T1, void, void, void>
{
public:
	tuple(T1 v1);

	T1 first() const;

	T1 arg0() const;

private:

	const T1 v1;

};

template <typename T1>
tuple<T1, void, void, void>::tuple(T1 v1)
: v1(v1)
{}

template <typename T1>
T1 tuple<T1, void, void, void>::first() const
{
	return this->v1;
}
template <typename T1>
T1 tuple<T1, void, void, void>::arg0() const
{
	return this->v1;
}









}

