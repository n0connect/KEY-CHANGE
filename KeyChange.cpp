#include <iostream>
#include <fstream>
#include <cmath>

/*
Diffie-Hellman-Anahtar-Değişimi
iki taraf arasında güvenli bir şekilde anahtar paylaşımını sağlar,

Üreteç (g): [2, p-1] aralığında bir sayı seçilir.
Özel sayılar (a ve b): [2, p-2] aralığında rastgele seçilen sayılar olmalıdır.

 - Alice ve Bob, birlikte kullanacakları bir asal sayı (p) ve bir üreteç (g) seçerler.
 - Alice, gizli anahtarını (a) seçer ve Bob, gizli anahtarını (b) seçer.
 - Alice, (g^a mod p) değerini hesaplar ve Bob'a gönderir.
 - Bob, (g^b mod p) değerini hesaplar ve Alice'e gönderir.
 - Alice, Bob'un gönderdiği değeri kullanarak ortak anahtarı hesaplar: (g^ab mod p).
 - Bob da Alice'in gönderdiği değeri kullanarak ortak anahtarı hesaplar: (g^ba mod p).
 - Sonuç olarak, Alice ve Bob'un sahip olduğu ortak anahtarlar birbirine eşittir.
*/

class KeyChanging {
	
	/*
	Sınıf Adı: KeyChanging
	Açıklama:
	  Bu sınıf Diffie-Hellman Anahtar Değiştirme algoritması için gerekli yapıyı oluşturur.
	Parametreler:
	 - PUBLIC_PRIME_NUMBER: Açık olarak belirlenecek asal sayı (p)
	 - SECRET_PRIVATE_NUMBER: [2, p-1] aralığında kişiye özel seçilir.
	 - PUBLIC_GENERATOR_NUMBER: [2, p-2] aralığında public belirlenir.
	Dönüş Değeri:
	  None, Türü KeyChanging Olan bir nesne oluşturur.
	*/

private:
	long long int     PUBLIC_PRIME_NUMBER{};
	long long int   SECRET_PRIVATE_NUMBER{};
	long long int PUBLIC_GENERATOR_NUMBER{};
	
public:

	KeyChanging(const char* NAME, long long int public_prime_number,
		long long int public_generator_number, long long int secret_private_number) {

		setPublicPrimeNumber(public_prime_number);
		setPublicGeneratorNumber(public_generator_number);
		setSecretPrivateNumber(secret_private_number);
		nonPrivatePublicArgs(NAME);
	}

	void setPublicPrimeNumber(long long int public_prime_number) {
		PUBLIC_PRIME_NUMBER = public_prime_number;
	}
	void setPublicGeneratorNumber(long long int public_generator_number) {
		PUBLIC_GENERATOR_NUMBER = public_generator_number;
	}
	void setSecretPrivateNumber(long long int secret_private_number) {
		SECRET_PRIVATE_NUMBER = secret_private_number;
	}
	long long int getPublicPrimeNumber() {
		return PUBLIC_PRIME_NUMBER;
	}
	long long int getPublicGeneratorNumber() {
		return PUBLIC_GENERATOR_NUMBER;
	}
	long long int getSecretPrivateNumber() {
		return SECRET_PRIVATE_NUMBER;
	}

	void nonPrivatePublicArgs(const char* NAME) {
		std::cout << std::endl << NAME << " - Public Gen-Key: " << PUBLIC_GENERATOR_NUMBER <<
			"  |  " << "Public Prime-Number: " << PUBLIC_PRIME_NUMBER << 
			"  |  "  << "Secret Key: " << SECRET_PRIVATE_NUMBER << std::endl;
	}

};

long long int SquareAndMultiply(long long int base, long long int exponent, long long int modulus) {

	/*
   Fonksiyon Adı: SquareAndMultiply
   Açıklama:
	 Bu fonksiyon, bir sayının diğer bir sayıya üssü alındıktan sonra belirli bir modül ile bölünmesini sağlar.
	 Bu, büyük sayılarla çalışırken kayan nokta hassasiyeti sorunlarını önlemek ve hızlı bir şekilde sonuç üretmek için kullanılır.
   Parametreler:
	 - base: Üs alınacak olan sayı
	 - exponent: Üs
	 - modulus: Modül değeri
   Dönüş Değeri:
	 Üs alınmış ve modül ile bölünmüş sonuç
   Notlar:
	 Bu fonksiyon, büyük sayılarla çalışırken kayan nokta hassasiyeti sorunlarını önlemek için
	 kayan nokta aritmetiği yerine tam sayılarla çalışır. Üs alma işleminin her adımında modüler aritmetiği kullanır.
	 Fonksiyon, hızlı bir üs alma algoritması olan "square and multiply" tekniğini uygular.
	*/

	long long int result = 1;
	base %= modulus; // Taban, modül ile bölündükten sonra modülün değeri alınır.

	while (exponent > 0) {

		// Eğer üs (exponent) tek ise.
		if (exponent & 1) result = (result * base) % modulus;

		base = (base * base) % modulus;
		exponent >>= 1; // Üs, sağa bir kaydırma işlemi (bölme işlemi).
	}

	return result;
}

void decryptTheKey(KeyChanging Alice, KeyChanging Bob) {
	// Alice için hesaplamalar.
	long long int ALICE_POW = SquareAndMultiply(Alice.getPublicGeneratorNumber(),
		Alice.getSecretPrivateNumber(), Alice.getPublicPrimeNumber());

	// Bob için hesaplamalar.
	long long int BOB_POW = SquareAndMultiply(Bob.getPublicGeneratorNumber(),
		Bob.getSecretPrivateNumber(), Bob.getPublicPrimeNumber());

	// Alice için hesaplamalar.
	long long int PROTECTED_ALICE_RESULT = SquareAndMultiply(BOB_POW,
		Alice.getSecretPrivateNumber(), Alice.getPublicPrimeNumber());

	// Bob için hesaplamalar.
	long long int PROTECTED_BOB_RESULT = SquareAndMultiply(ALICE_POW,
		Bob.getSecretPrivateNumber(), Bob.getPublicPrimeNumber());

	std::cout << std::endl << "Alice Result: " << PROTECTED_ALICE_RESULT << std::endl;
	std::cout << "Bob Result: " << PROTECTED_BOB_RESULT << std::endl;
}



int main() {

	long long int PUBLIC_PRIME{};
	long long int PUBLIC_GENERATOR{};

	long long int PRIVATE_ALICE{};
	long long int PRIVATE_BOB{};

	std::cout <<
		"Diffie-Hellman-Key-Change\n"									       <<
		"enables secure key sharing between the two parties,\n               " <<
		std::endl															   <<
		"Prime(p) : A prime number with a relatively large public.\n"          <<
		"Generator(g) : [2, p - 1] a number is selected in the range.\n"	   <<
		"Private(a ve b) : [2, p - 2] randomly selected numbers in the interval." << std::endl;

	// TRY-EXCEPT BLOKLARI ES GEÇİLDİ.
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
