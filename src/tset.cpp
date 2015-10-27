// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower( bf.GetLength() )
{

}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower)
		return 0;
	if (BitField != s.BitField) 
		return 0;
	return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	int n = 1;
	if (MaxPower == s.MaxPower){
		if (BitField != s.BitField)
			n = 1;
		else
			n = 0;
	}
	return n;
}
TSet TSet::operator+(const TSet &s) // объединение
{
	TBitField tmp(MaxPower);
	tmp = BitField | s.BitField;
	TSet tmpS(tmp);
	return tmpS;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	BitField.SetBit(Elem);
	return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	BitField.ClrBit(Elem);
	return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TBitField tmp(MaxPower);
	tmp = BitField & s.BitField;
	TSet _s(tmp);
	return _s;
}

TSet TSet::operator~(void) // дополнение
{
	BitField = ~BitField;
	return *this;
}

// перегрузка ввода/вывода

istream &operator>>(istream &is, TSet &s) // ввод
{	
	int i = 0; is >> i;
	while ((i >= 0) && (i < s.MaxPower)){
		s.InsElem(i);
		is >> i;
	}
	return is;
}

ostream& operator<<(ostream &os, const TSet &s) // вывод
{
	os << s.BitField;
	return os;
}
