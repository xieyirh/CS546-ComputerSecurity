import java.io.IOException;

public class FHEv2 {

	public static void main(String[] args) throws IOException {
		if(args.length == 5 && args[0].equals("-k")) {
			int keySize = Integer.parseInt(args[1]);
			int w = Integer.parseInt(args[2]);
			int z = Integer.parseInt(args[3]);
			int k = 5; //5 consecutive homomorphic multiplication
			if (keySize < (k + 1) * (w + z)) {
				System.out.println("key size should be at least (k + 1)(w + z)!");
				return;
			}
			Key keys = new Key(keySize,w, z, args[4]);
			keys.keyGenV2();
			System.out.println("Key File generated!");
		}
		else if(args.length == 3 && args[0].equals("-p")) {
			FHE fhe = new FHE(args[1], args[2]);
			String paddedMessage = fhe.messagePadding(args[1]);
			if(paddedMessage != null) {
				System.out.println("Padded message = " + paddedMessage);
			}
			else {
				System.out.println("Message padding fails!");
				return;
			}
		}
		else if(args.length == 3 && args[0].equals("-e")) {
			FHE fhe1 = new FHE(args[1], args[2]);
			String paddedMessage = fhe1.messagePadding(args[1]);
			FHE fhe2 = new FHE(paddedMessage, args[2]);
			String cipher = fhe2.encryption();
			if(cipher != null) {
				System.out.println("cipher = " + cipher);
			}
			else {
				System.out.println("Message is bigger than p1!");
				return;
			}
		}
		else if(args.length == 3 && args[0].equals("-d")) {
			FHE fhe = new FHE(args[1], args[2]);
			String plainText = fhe.decryptionV2();
			if(plainText != null) {
				System.out.println("Plaintext = " + plainText);
			}
			else {
				System.out.println("Decryption error!");
				return;
			}
		}
		else if(args.length == 3 && args[0].equals("-b")) {
			System.out.println("Message = " + args[1]);
			
			FHE fhe1 = new FHE(args[1], args[2]);
			String paddedMessage = fhe1.messagePadding(args[1]);
			if(paddedMessage == null) {
				System.out.println("Imax is bigger than 2^w!");
				return;
			}
			FHE fhe2 = new FHE(paddedMessage, args[2]);
			String cipher = fhe2.encryption();

			if(cipher != null) {
				System.out.println("Cipher = " + cipher );
			}
			else {
				System.out.println("Encryption error!");
				return;
			}
			FHE fhe3 = new FHE(cipher, args[2]);
			String plainText = fhe3.decryptionV2();
			if(plainText != null) {
				System.out.println("Plaintext = " + plainText);
			}
			else {
				System.out.println("Decryption error!");
				return;
			}
		}
		else if(args.length == 4 && args[0].equals("-a")) {
			FHE fhe = new FHE(args[1],args[2],args[3]);
			String cipherAddition = fhe.addition(args[1], args[2]);
			if(cipherAddition != null) {
				System.out.println("Cipher addition  = " + cipherAddition );
			}
			else {
				System.out.println("Cipher Addition error!");
				return;
			}
		}
		else if(args.length == 6 && args[0].equals("-a") && args[1].equals("-e") && args[3].equals("-e")) {
			FHE fhe1 = new FHE(args[2], args[5]);
			FHE fhe2 = new FHE(args[4], args[5]);
			String paddedMessage1 = fhe1.messagePadding(args[2]);
			String paddedMessage2 = fhe2.messagePadding(args[4]);
			FHE fhe3 = new FHE(paddedMessage1, args[5]);
			FHE fhe4 = new FHE(paddedMessage2, args[5]);
			String cipher1 =fhe3.encryption();
			String cipher2 = fhe4.encryption();
			if(paddedMessage1== null || paddedMessage2 == null) {
				System.out.println("Imaxs are bigger than 2^w!");
				return;
			}
			
			FHE fhe = new FHE(cipher1,cipher2,args[5]);
			String cipherAddition = fhe.addition(cipher1, cipher2);
			if(cipherAddition != null) {
				System.out.println("Cipher addition  = " + cipherAddition );
			}
			else {
				System.out.println("Cipher Addition error!");
				return;
			}
		}
		else if(args.length == 4 && args[0].equals("-m")) {
			FHE fhe = new FHE(args[1],args[2],args[3]);
			String cipherMultiplication = fhe.multiplication(args[1], args[2]);
			if(cipherMultiplication != null) {
				System.out.println("Cipher multiplication  = " + cipherMultiplication );
			}
			else {
				System.out.println("Cipher multiplication error!");
				return;
			}
		}
		else if(args.length == 6 && args[0].equals("-m") && args[1].equals("-e") && args[3].equals("-e")) {
			FHE fhe1 = new FHE(args[2], args[5]);
			FHE fhe2 = new FHE(args[4], args[5]);
			String paddedMessage1 = fhe1.messagePadding(args[2]);
			String paddedMessage2 = fhe2.messagePadding(args[4]);
			FHE fhe3 = new FHE(paddedMessage1, args[5]);
			FHE fhe4 = new FHE(paddedMessage2, args[5]);
			String cipher1 =fhe3.encryption();
			String cipher2 = fhe4.encryption();
			if(paddedMessage1== null || paddedMessage2 == null) {
				System.out.println("Imaxs are bigger than 2^w!");
				return;
			}
			
			FHE fhe = new FHE(cipher1,cipher2,args[5]);
			String cipherMultiplication = fhe.multiplication(cipher1, cipher2);
			if(cipherMultiplication != null) {
				System.out.println("Cipher multiplication  = " + cipherMultiplication );
			}
			else {
				System.out.println("Cipher multiplication error!");
				return;
			}
		}
		else {
			System.out.println("Usage: FHEv2 -k <key size> <KeyFileName>\n");
	        System.out.println("       FHEv2 -e <m> <KeyFileName>\n");
	        System.out.println("       FHEv2 -d <Cm> <KeyFileName>\n");
	        System.out.println("       FHEv2 -b <m> <KeyFileName>\n");
	        System.out.println("       FHEV2 -a <-e <m1> | Cm1>,<-e <m2> | Cm2> <keyFileName>\n");
	        System.out.println("       FHEV2 -m <-e <m1> | Cm1>,<-e <m2> | Cm2> <keyFileName>\n");
		}
	}

}