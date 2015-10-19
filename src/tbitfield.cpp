// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len = 10)
{
	BitLen = len;
	MemLen = BitLen / (sizeof(TELEM)* 8) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++){
		pMem[i] = 0;
	}
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
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n / (sizeof(TELEM)* 8) + 1);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int tmp = n % (sizeof(TELEM)* 8);
	TELEM mask = 1 << tmp;
	return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n); // побитовое ИЛИ
}

void TBitField::ClrBit(const int n) // очистить бит
{
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);  // побитовое И
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	int tmp = pMem[GetMemIndex(n)];
	tmp = pMem[GetMemIndex(n)] & GetMemMask(n);
	if (tmp != 0){
		return 1;
	}
	else return 0;
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
	if (BitLen == bf.BitLen){
		for (int i = 0; i < MemLen; i++){
			if (pMem[i] != bf.pMem[i]){
				return 0;
			}
		}
	}
	else {
		return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen){
		for (int i = 0; i < MemLen; i++){
			if (pMem[i] != bf.pMem[i]){
				return 1;
			}
		}
	}
	else {
		return 1;
	}
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField tmp(BitLen);
	for (int i = 0; i < MemLen; i++){
		tmp.pMem[i] = pMem[i] | bf.pMem[i];
	}
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField tmp(BitLen);
	for (int i = 0; i < MemLen; i++){
		tmp.pMem[i] = pMem[i] & bf.pMem[i];
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

// ввод/вывод

/*istream &operator>>(istream &is, TBitField &bf) // ввод
{


}