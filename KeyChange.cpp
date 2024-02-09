#include <iostream>
#include <fstream>
#include <cmath>

/*
Diffie-Hellman-Anahtar-De�i�imi
iki taraf aras�nda g�venli bir �ekilde anahtar payla��m�n� sa�lar,

�rete� (g): [2, p-1] aral���nda bir say� se�ilir.
�zel say�lar (a ve b): [2, p-2] aral���nda rastgele se�ilen say�lar olmal�d�r.

 - Alice ve Bob, birlikte kullanacaklar� bir asal say� (p) ve bir �rete� (g) se�erler.
 - Alice, gizli anahtar�n� (a) se�er ve Bob, gizli anahtar�n� (b) se�er.
 - Alice, (g^a mod p) de�erini hesaplar ve Bob'a g�nderir.
 - Bob, (g^b mod p) de�erini hesaplar ve Alice'e g�nderir.
 - Alice, Bob'un g�nderdi�i de�eri kullanarak ortak anahtar� hesaplar: (g^ab mod p).
 - Bob da Alice'in g�nderdi�i de�eri kullanarak ortak anahtar� hesaplar: (g^ba mod p).
 - Sonu� olarak, Alice ve Bob'un sahip oldu�u ortak anahtarlar birbirine e�ittir.
*/

class KeyChanging {
	
	/*
	S�n�f Ad�: KeyChanging
	A��klama:
	  Bu s�n�f Diffie-Hellman Anahtar De�i�tirme algoritmas� i�in gerekli yap�y� olu�turur.
	Parametreler:
	 - PUBLIC_PRIME_NUMBER: A��k olarak belirlenecek asal say� (p)
	 - SECRET_PRIVATE_NUMBER: [2, p-1] aral���nda ki�iye �zel se�ilir.
	 - PUBLIC_GENERATOR_NUMBER: [2, p-2] aral���nda public belirlenir.
	D�n�� De�eri:
	  None, T�r� KeyChanging Olan bir nesne olu�turur.
	*/

private:
	long long     PUBLIC_PRIME_NUMBER{};
	long long   SECRET_PRIVATE_NUMBER{};
	long long PUBLIC_GENERATOR_NUMBER{};
	
public:

	KeyChanging(const char* NAME, long long public_prime_number,
		long long public_generator_number, long long secret_private_number) {

		setPublicPrimeNumber(public_prime_number);
		setPublicGeneratorNumber(public_generator_number);
		setSecretPrivateNumber(secret_private_number);
		nonPrivatePublicArgs(NAME);
	}

	void setPublicPrimeNumber(long long public_prime_number) {
		PUBLIC_PRIME_NUMBER = public_prime_number;
	}
	void setPublicGeneratorNumber(long long public_generator_number) {
		PUBLIC_GENERATOR_NUMBER = public_generator_number;
	}
	void setSecretPrivateNumber(long long secret_private_number) {
		SECRET_PRIVATE_NUMBER = secret_private_number;
	}
	long long getPublicPrimeNumber() {
		return PUBLIC_PRIME_NUMBER;
	}
	long long getPublicGeneratorNumber() {
		return PUBLIC_GENERATOR_NUMBER;
	}
	long long getSecretPrivateNumber() {
		return SECRET_PRIVATE_NUMBER;
	}

	void nonPrivatePublicArgs(const char* NAME) {
		std::cout << std::endl << NAME << " - Public Gen-Key: " << PUBLIC_GENERATOR_NUMBER <<
			"  |  " << "Public Prime-Number: " << PUBLIC_PRIME_NUMBER << 
			"  |  "  << "Secret Key: " << SECRET_PRIVATE_NUMBER << std::endl;
	}

};

long long SquareAndMultiply(long long base, long long exponent, long long modulus) {

	/*
   Fonksiyon Ad�: SquareAndMultiply
   A��klama:
	 Bu fonksiyon, bir say�n�n di�er bir say�ya �ss� al�nd�ktan sonra belirli bir mod�l ile b�l�nmesini sa�lar.
	 Bu, b�y�k say�larla �al���rken kayan nokta hassasiyeti sorunlar�n� �nlemek ve h�zl� bir �ekilde sonu� �retmek i�in kullan�l�r.
   Parametreler:
	 - base: �s al�nacak olan say�
	 - exponent: �s
	 - modulus: Mod�l de�eri
   D�n�� De�eri:
	 �s al�nm�� ve mod�l ile b�l�nm�� sonu�
   Notlar:
	 Bu fonksiyon, b�y�k say�larla �al���rken kayan nokta hassasiyeti sorunlar�n� �nlemek i�in
	 kayan nokta aritmeti�i yerine tam say�larla �al���r. �s alma i�leminin her ad�m�nda mod�ler aritmeti�i kullan�r.
	 Fonksiyon, h�zl� bir �s alma algoritmas� olan "square and multiply" tekni�ini uygular.
	*/

	long long result = 1;
	base %= modulus; // Taban, mod�l ile b�l�nd�kten sonra mod�l�n de�eri al�n�r.

	while (exponent > 0) {

		// E�er �s (exponent) tek ise.
		if (exponent & 1) result = (result * base) % modulus;

		base = (base * base) % modulus;
		exponent >>= 1; // �s, sa�a bir kayd�rma i�lemi (b�lme i�lemi).
	}

	return result;
}

void decryptTheKey(KeyChanging Alice, KeyChanging Bob) {
	// Alice i�in hesaplamalar.
	long long ALICE_POW = SquareAndMultiply(Alice.getPublicGeneratorNumber(), Alice.getSecretPrivateNumber(), Alice.getPublicPrimeNumber());

	// Bob i�in hesaplamalar.
	long long BOB_POW = SquareAndMultiply(Bob.getPublicGeneratorNumber(), Bob.getSecretPrivateNumber(), Bob.getPublicPrimeNumber());

	// Alice i�in hesaplamalar.
	long long PROTECTED_ALICE_RESULT = SquareAndMultiply(BOB_POW, Alice.getSecretPrivateNumber(), Alice.getPublicPrimeNumber());

	// Bob i�in hesaplamalar.
	long long PROTECTED_BOB_RESULT = SquareAndMultiply(ALICE_POW, Bob.getSecretPrivateNumber(), Bob.getPublicPrimeNumber());

	std::cout << std::endl << "Alice Result: " << PROTECTED_ALICE_RESULT << std::endl;
	std::cout << "Bob Result: " << PROTECTED_BOB_RESULT << std::endl;
}



int main() {

	long long PUBLIC_PRIME{};
	long long PUBLIC_GENERATOR{};

	long long PRIVATE_ALICE{};
	long long PRIVATE_BOB{};

	std::cout <<
		"Diffie-Hellman-Key-Change\n"									       <<
		"enables secure key sharing between the two parties,\n               " <<
		std::endl															   <<
		"Prime(p) : A prime number with a relatively large public.\n"          <<
		"Generator(g) : [2, p - 1] a number is selected in the range.\n"	   <<
		"Private(a ve b) : [2, p - 2] randomly selected numbers in the interval." << std::endl;

	// TRY-EXCEPT BLOKLARI ES GE��LD�.
	std::cout << "\nPUBLIC PRIME: ";
	std::cin >> PUBLIC_PRIME;
	std::cout << "PUBLIC GENERATOR: ";
	std::cin >> PUBLIC_GENERATOR;
	std::cout << "PRIVATE ALICE: ";
	std::cin >> PRIVATE_ALICE;
	std::cout << "PRIVATE BOB: ";
	std::cin >> PRIVATE_BOB;
	std::cout << std::endl;

	KeyChanging alice("Alice", PUBLIC_PRIME, PUBLIC_GENERATOR, PRIVATE_ALICE);
	KeyChanging bobe("Bobe", PUBLIC_PRIME, PUBLIC_GENERATOR, PRIVATE_BOB);

	decryptTheKey(alice, bobe);

}