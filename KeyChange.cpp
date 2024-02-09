#include <iostream>
#include <fstream>
#include <cmath>

/*
Diffie-Hellman-Anahtar-Deðiþimi
iki taraf arasýnda güvenli bir þekilde anahtar paylaþýmýný saðlar,

Üreteç (g): [2, p-1] aralýðýnda bir sayý seçilir.
Özel sayýlar (a ve b): [2, p-2] aralýðýnda rastgele seçilen sayýlar olmalýdýr.

 - Alice ve Bob, birlikte kullanacaklarý bir asal sayý (p) ve bir üreteç (g) seçerler.
 - Alice, gizli anahtarýný (a) seçer ve Bob, gizli anahtarýný (b) seçer.
 - Alice, (g^a mod p) deðerini hesaplar ve Bob'a gönderir.
 - Bob, (g^b mod p) deðerini hesaplar ve Alice'e gönderir.
 - Alice, Bob'un gönderdiði deðeri kullanarak ortak anahtarý hesaplar: (g^ab mod p).
 - Bob da Alice'in gönderdiði deðeri kullanarak ortak anahtarý hesaplar: (g^ba mod p).
 - Sonuç olarak, Alice ve Bob'un sahip olduðu ortak anahtarlar birbirine eþittir.
*/

class KeyChanging {
	
	/*
	Sýnýf Adý: KeyChanging
	Açýklama:
	  Bu sýnýf Diffie-Hellman Anahtar Deðiþtirme algoritmasý için gerekli yapýyý oluþturur.
	Parametreler:
	 - PUBLIC_PRIME_NUMBER: Açýk olarak belirlenecek asal sayý (p)
	 - SECRET_PRIVATE_NUMBER: [2, p-1] aralýðýnda kiþiye özel seçilir.
	 - PUBLIC_GENERATOR_NUMBER: [2, p-2] aralýðýnda public belirlenir.
	Dönüþ Deðeri:
	  None, Türü KeyChanging Olan bir nesne oluþturur.
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
   Fonksiyon Adý: SquareAndMultiply
   Açýklama:
	 Bu fonksiyon, bir sayýnýn diðer bir sayýya üssü alýndýktan sonra belirli bir modül ile bölünmesini saðlar.
	 Bu, büyük sayýlarla çalýþýrken kayan nokta hassasiyeti sorunlarýný önlemek ve hýzlý bir þekilde sonuç üretmek için kullanýlýr.
   Parametreler:
	 - base: Üs alýnacak olan sayý
	 - exponent: Üs
	 - modulus: Modül deðeri
   Dönüþ Deðeri:
	 Üs alýnmýþ ve modül ile bölünmüþ sonuç
   Notlar:
	 Bu fonksiyon, büyük sayýlarla çalýþýrken kayan nokta hassasiyeti sorunlarýný önlemek için
	 kayan nokta aritmetiði yerine tam sayýlarla çalýþýr. Üs alma iþleminin her adýmýnda modüler aritmetiði kullanýr.
	 Fonksiyon, hýzlý bir üs alma algoritmasý olan "square and multiply" tekniðini uygular.
	*/

	long long result = 1;
	base %= modulus; // Taban, modül ile bölündükten sonra modülün deðeri alýnýr.

	while (exponent > 0) {

		// Eðer üs (exponent) tek ise.
		if (exponent & 1) result = (result * base) % modulus;

		base = (base * base) % modulus;
		exponent >>= 1; // Üs, saða bir kaydýrma iþlemi (bölme iþlemi).
	}

	return result;
}

void decryptTheKey(KeyChanging Alice, KeyChanging Bob) {
	// Alice için hesaplamalar.
	long long ALICE_POW = SquareAndMultiply(Alice.getPublicGeneratorNumber(), Alice.getSecretPrivateNumber(), Alice.getPublicPrimeNumber());

	// Bob için hesaplamalar.
	long long BOB_POW = SquareAndMultiply(Bob.getPublicGeneratorNumber(), Bob.getSecretPrivateNumber(), Bob.getPublicPrimeNumber());

	// Alice için hesaplamalar.
	long long PROTECTED_ALICE_RESULT = SquareAndMultiply(BOB_POW, Alice.getSecretPrivateNumber(), Alice.getPublicPrimeNumber());

	// Bob için hesaplamalar.
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

	// TRY-EXCEPT BLOKLARI ES GEÇÝLDÝ.
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