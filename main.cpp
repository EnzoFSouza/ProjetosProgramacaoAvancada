#include <iostream>
#include "bigint.h"

using namespace std;

int main(void)
{
  BigInt BI0(0), BI1(1), BIm1(-1),
         BIbig(1234567890), BImbig(-1234567890), BIbig1(1234567891);

  cout << "CONFIRA SE AS RESPOSTAS SIM/NAO GERADAS PELO PROGRAMA ESTAO CORRETAS\n\n";

  // Teste do valor absoluto
  cout << "\nTESTE DO ABS:\n";
  cout << "I01:\t" << "BI=" << BI0 << "\tabs(BI)=" << abs(BI0) << endl;
  cout << "I02:\t" << "BI=" << BI1 << "\tabs(BI)=" << abs(BI1) << endl;
  cout << "I03:\t" << "BI=" << BIm1 << "\tabs(BI)=" << abs(BIm1) << endl;
  cout << "I05:\t" << "BI=" << BIbig << "\tabs(BI)=" << abs(BIbig) << endl;
  cout << "I06:\t" << "BI=" << BImbig << "\tabs(BI)=" << abs(BImbig) << endl;

  // Teste da igualdade
  cout << "\nTESTE DA IGUALDADE:\n";
  cout << "I07:\t" << BI0 << "==" << BI0 << " ? " << (BI0==BI0 ? "SIM" : "NAO") << endl;
  cout << "I08:\t" << BI0 << "==" << BigInt() << " ? " << (BI0==BigInt() ? "SIM" : "NAO") << endl;
  cout << "I09:\t" << BI0 << "==" << BI1 << " ? " << (BI0==BI1 ? "SIM" : "NAO") << endl;
  cout << "I10:\t" << BigInt(1) << "==" << BI1 << " ? " << (BigInt(1)==BI1 ? "SIM" : "NAO") << endl;
  cout << "I11:\t" << BIm1 << "==" << BI1 << " ? " << (BIm1==BI1 ? "SIM" : "NAO") << endl;
  cout << "I12:\t" << BIbig << "==" << BI1 << " ? " << (BIbig==BI1 ? "SIM" : "NAO") << endl;
  cout << "I13:\t" << BIbig << "==" << BIbig << " ? " << (BIbig==BIbig ? "SIM" : "NAO") << endl;
  cout << "I14:\t" << BIbig << "==" << BImbig << " ? " << (BIbig==BImbig ? "SIM" : "NAO") << endl;

  // Teste da desigualdade
  cout << "\nTESTE DA DESIGUALDADE:\n";
  cout << "I15:\t" << BI0 << "!=" << BI0 << " ? " << (BI0!=BI0 ? "SIM" : "NAO") << endl;
  cout << "I16:\t" << BI0 << "!=" << BigInt() << " ? " << (BI0!=BigInt() ? "SIM" : "NAO") << endl;
  cout << "I17:\t" << BI0 << "!=" << BI1 << " ? " << (BI0!=BI1 ? "SIM" : "NAO") << endl;
  cout << "I18:\t" << BigInt(1) << "!=" << BI1 << " ? " << (BigInt(1)!=BI1 ? "SIM" : "NAO") << endl;
  cout << "I19:\t" << BIm1 << "!=" << BI1 << " ? " << (BIm1!=BI1 ? "SIM" : "NAO") << endl;
  cout << "I20:\t" << BIbig << "!=" << BI1 << " ? " << (BIbig!=BI1 ? "SIM" : "NAO") << endl;
  cout << "I21:\t" << BIbig << "!=" << BIbig << " ? " << (BIbig!=BIbig ? "SIM" : "NAO") << endl;
  cout << "I22:\t" << BIbig << "!=" << BImbig << " ? " << (BIbig!=BImbig ? "SIM" : "NAO") << endl;

  // Teste do <
  cout << "\nTESTE DO <:\n";
  cout << "I23:\t" << BIm1 << "<" << BI0 << " ? " << (BIm1<BI0 ? "SIM" : "NAO") << endl;
  cout << "I24:\t" << BI1 << "<" << BIm1 << " ? " << (BI1<BIm1 ? "SIM" : "NAO") << endl;
  cout << "I25:\t" << BImbig << "<" << BIm1 << " ? " << (BImbig<BIm1 ? "SIM" : "NAO") << endl;
  cout << "I26:\t" << BIm1 << "<" << BImbig << " ? " << (BIm1<BImbig ? "SIM" : "NAO") << endl;
  cout << "I27:\t" << BI1 << "<" << BIbig << " ? " << (BI1<BIbig ? "SIM" : "NAO") << endl;
  cout << "I28:\t" << BIbig << "<" << BI1 << " ? " << (BIbig<BI1 ? "SIM" : "NAO") << endl;
  cout << "I29:\t" << BIbig << "<" << BIbig1 << " ? " << (BIbig<BIbig1 ? "SIM" : "NAO") << endl;
  cout << "I30:\t" << BIbig1 << "<" << BIbig << " ? " << (BIbig1<BIbig ? "SIM" : "NAO") << endl;
  cout << "I31:\t" << BI0 << "<" << BI0 << " ? " << (BI0<BI0 ? "SIM" : "NAO") << endl;
  cout << "I32:\t" << BI1 << "<" << BI1 << " ? " << (BI1<BI1 ? "SIM" : "NAO") << endl;
  cout << "I33:\t" << BIbig << "<" << BIbig << " ? " << (BIbig<BIbig ? "SIM" : "NAO") << endl;

  // Teste do <=
  cout << "\nTESTE DO <=:\n";
  cout << "I34:\t" << BIm1 << "<=" << BI0 << " ? " << (BIm1<=BI0 ? "SIM" : "NAO") << endl;
  cout << "I35:\t" << BI1 << "<=" << BIm1 << " ? " << (BI1<=BIm1 ? "SIM" : "NAO") << endl;
  cout << "I36:\t" << BImbig << "<=" << BIm1 << " ? " << (BImbig<=BIm1 ? "SIM" : "NAO") << endl;
  cout << "I37:\t" << BIm1 << "<=" << BImbig << " ? " << (BIm1<=BImbig ? "SIM" : "NAO") << endl;
  cout << "I38:\t" << BI1 << "<=" << BIbig << " ? " << (BI1<=BIbig ? "SIM" : "NAO") << endl;
  cout << "I39:\t" << BIbig << "<=" << BI1 << " ? " << (BIbig<=BI1 ? "SIM" : "NAO") << endl;
  cout << "I40:\t" << BIbig << "<=" << BIbig1 << " ? " << (BIbig<=BIbig1 ? "SIM" : "NAO") << endl;
  cout << "I41:\t" << BIbig1 << "<=" << BIbig << " ? " << (BIbig1<=BIbig ? "SIM" : "NAO") << endl;
  cout << "I42:\t" << BI0 << "<=" << BI0 << " ? " << (BI0<=BI0 ? "SIM" : "NAO") << endl;
  cout << "I43:\t" << BI1 << "<=" << BI1 << " ? " << (BI1<=BI1 ? "SIM" : "NAO") << endl;
  cout << "I44:\t" << BIbig << "<=" << BIbig << " ? " << (BIbig<=BIbig ? "SIM" : "NAO") << endl;

  // Teste do >
  cout << "\nTESTE DO >:\n";
  cout << "I45:\t" << BIm1 << ">" << BI0 << " ? " << (BIm1>BI0 ? "SIM" : "NAO") << endl;
  cout << "I46:\t" << BI1 << ">" << BIm1 << " ? " << (BI1>BIm1 ? "SIM" : "NAO") << endl;
  cout << "I47:\t" << BImbig << ">" << BIm1 << " ? " << (BImbig>BIm1 ? "SIM" : "NAO") << endl;
  cout << "I48:\t" << BIm1 << ">" << BImbig << " ? " << (BIm1>BImbig ? "SIM" : "NAO") << endl;
  cout << "I49:\t" << BI1 << ">" << BIbig << " ? " << (BI1>BIbig ? "SIM" : "NAO") << endl;
  cout << "I50:\t" << BIbig << ">" << BI1 << " ? " << (BIbig>BI1 ? "SIM" : "NAO") << endl;
  cout << "I51:\t" << BIbig << ">" << BIbig1 << " ? " << (BIbig>BIbig1 ? "SIM" : "NAO") << endl;
  cout << "I52:\t" << BIbig1 << ">" << BIbig << " ? " << (BIbig1>BIbig ? "SIM" : "NAO") << endl;
  cout << "I53:\t" << BI0 << ">" << BI0 << " ? " << (BI0>BI0 ? "SIM" : "NAO") << endl;
  cout << "I54:\t" << BI1 << ">" << BI1 << " ? " << (BI1>BI1 ? "SIM" : "NAO") << endl;
  cout << "I55:\t" << BIbig << ">" << BIbig << " ? " << (BIbig>BIbig ? "SIM" : "NAO") << endl;

  // Teste do >=
  cout << "\nTESTE DO >=:\n";
  cout << "I56:\t" << BIm1 << ">=" << BI0 << " ? " << (BIm1>=BI0 ? "SIM" : "NAO") << endl;
  cout << "I57:\t" << BI1 << ">=" << BIm1 << " ? " << (BI1>=BIm1 ? "SIM" : "NAO") << endl;
  cout << "I58:\t" << BImbig << ">=" << BIm1 << " ? " << (BImbig>=BIm1 ? "SIM" : "NAO") << endl;
  cout << "I59:\t" << BIm1 << ">=" << BImbig << " ? " << (BIm1>=BImbig ? "SIM" : "NAO") << endl;
  cout << "I60:\t" << BI1 << ">=" << BIbig << " ? " << (BI1>=BIbig ? "SIM" : "NAO") << endl;
  cout << "I61:\t" << BIbig << ">=" << BI1 << " ? " << (BIbig>=BI1 ? "SIM" : "NAO") << endl;
  cout << "I62:\t" << BIbig << ">=" << BIbig1 << " ? " << (BIbig>=BIbig1 ? "SIM" : "NAO") << endl;
  cout << "I63:\t" << BIbig1 << ">=" << BIbig << " ? " << (BIbig1>=BIbig ? "SIM" : "NAO") << endl;
  cout << "I64:\t" << BI0 << ">=" << BI0 << " ? " << (BI0>=BI0 ? "SIM" : "NAO") << endl;
  cout << "I65:\t" << BI1 << ">=" << BI1 << " ? " << (BI1>=BI1 ? "SIM" : "NAO") << endl;
  cout << "I66:\t" << BIbig << ">=" << BIbig << " ? " << (BIbig>=BIbig ? "SIM" : "NAO") << endl;

  return 0;
}

