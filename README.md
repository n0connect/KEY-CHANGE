# Diffie-Hellman Key Exchange Algorithm

The Diffie-Hellman key exchange algorithm, also known as the Diffie-Hellman protocol, enables secure key sharing between two parties over an insecure communication channel. It allows both parties to agree upon a shared secret key without directly transmitting it.

## How it Works

1. **Initialization**:
   - Both parties, let's call them Alice and Bob, agree on two public parameters: a prime number \( p \) and a base \( g \), where \( g \) is a primitive root modulo \( p \). These parameters are publicly known.

2. **Key Generation**:
   - Each party generates their own private key. Alice chooses a private key \( a \) and Bob chooses a private key \( b \). These private keys are kept secret.

3. **Public Key Calculation**:
   - Alice computes her public key \( A = g^a \mod p \) and sends it to Bob.
   - Bob computes his public key \( B = g^b \mod p \) and sends it to Alice.

4. **Shared Secret Calculation**:
   - Upon receiving the public key from the other party, each party computes the shared secret using their own private key and the received public key.
   - Alice computes \( s = B^a \mod p \) and Bob computes \( s = A^b \mod p \).
   - Both parties arrive at the same shared secret \( s \), which can be used as the encryption key for secure communication.

## Implementation Details

This implementation consists of the following components:

- **KeyChanging Class**: 
  - Represents the structure required for the Diffie-Hellman key exchange algorithm, including public prime number, public generator number, and private secret number.

- **SquareAndMultiply Function**: 
  - Implements the square and multiply algorithm to perform modular exponentiation efficiently, which is a crucial part of the Diffie-Hellman key exchange.

- **decryptTheKey Function**:
  - Performs the key exchange process between two parties, Alice and Bob, based on their private and public parameters.

## Usage

1. Enter the public prime number (\( p \)) and public generator number (\( g \)).
2. Enter the private keys for both Alice and Bob.
3. The program will calculate the shared secret key for both parties and display the results.

## About

This implementation serves as a demonstration of the Diffie-Hellman key exchange algorithm in action, providing a practical understanding of how secure key sharing can be achieved in cryptographic protocols.
