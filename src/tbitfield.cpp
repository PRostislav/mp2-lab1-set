// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len=10)
{
	if (len > 0) {
		BitLen = len;
		MemLen = BitLen / (sizeof(TELEM)* 8) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++){
			pMem[i] = 0;
		}
	}
	else throw len;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++){
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int tmp = (n / (sizeof(TELEM)* 8));
	return (tmp);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n 
{
	int Pos = n % 32;
	TELEM temp = 1;
	temp = temp << Pos;
	return temp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n >= 0) && (n<BitLen)){
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n); // побитовое ИЛИ
	}
	else throw n;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= 0) && (n < BitLen)){
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);  // побитовое И
	}
	else throw n;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= 0) && (n < BitLen)){
		int tmp = pMem[GetMemIndex(n)];
		tmp &= GetMemMask(n);

		if (tmp != 0){
			return 1;
		}
		else return 0;
	}
	else throw n;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++){
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	for (int i = 0; i < BitLen; i++){
		if (GetBit(i) != bf.GetBit(i))
			return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int n = 0;
	for (int i = 0; i < BitLen; i++){
		if (GetBit(i) != bf.GetBit(i))
			n=1;
	}
	return n;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (bf.BitLen == BitLen){
		TBitField tmp(BitLen);
		for (int i = 0; i < MemLen; i++){
			tmp.pMem[i] = pMem[i] | bf.pMem[i];
		}
		return tmp;
	}
	else {
		int max = 0, min = 0;
		TBitField tmp;
		if (BitLen < bf.BitLen){
			max = bf.MemLen;
			min = MemLen;
			tmp=bf;
			for (int i = 0; i <= min; i++)
				tmp.pMem[tmp.MemLen - i] = tmp.pMem[tmp.MemLen - i] | pMem[MemLen - i];
			return tmp;
		}
		else {
			max = MemLen;
			min = bf.MemLen;
			tmp = *this;
			for (int i = 0; i <= min; i++)
				tmp.pMem[tmp.MemLen - i] = tmp.pMem[tmp.MemLen - i] | bf.pMem[bf.MemLen - i];
			return tmp;
		}
	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int tmpsize = 0;
	int n = 0;
	if (BitLen >= bf.BitLen)
	{
		tmpsize = BitLen;
		n = bf.BitLen;
	}
	else
	{
		tmpsize = bf.BitLen;
		n = BitLen;
	}

	TBitField tmp(tmpsize);
	for (int i = 0; i < n; i++){
		if (GetBit(i) && bf.GetBit(i))
			tmp.SetBit(i);
	}
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i = 0; i < MemLen; i++){
		tmp.pMem[i] = ~pMem[i];
	}
	return tmp;
}

//ввод вывод

istream &operator>>(istream &is, TBitField &bf) // ввод
{	int i=0; 
	char ch; 
	do {i>>ch;}
	while (ch!=' ');

	while (1) 
	{ 
		is>>ch; 
		if (ch=='0') 
		bf.ClrBit(i++); 
		else if (ch=='1') 
			bf.SetBit(i++); 
	else break; 
	} 
return is;
}

ostream &operator<<(ostream &os, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++){
		if (bf.GetBit(i)) 
			os << 1;
		else os << 0;	
	}
	return os;
}