import java.io.IOException;

public class FHEv1 {

	public static void main(String[] args) throws IOException {
		if(args.length == 3 && args[0].equals("-k")) {
			int keySize = Integer.parseInt(args[1]);
			Key keys = new Key(keySize, args[2]);
			keys.keyGen();
			System.out.println("Key File generated!");
		}
		else if(args.length == 3 && args[0].equals("-e")) {
			FHE fhe = new FHE(args[1], args[2]);
			String cipher = fhe.encryption();
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
			String plainText = fhe.decryption();
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
			String cipher =fhe1.encryption();
			if(cipher != null) {
				System.out.println("Cipher = " + cipher );
			}
			else {
				System.out.println("Encryption error!");
				return;
			}
			FHE fhe2 = new FHE(cipher, args[2]);
			String plainText = fhe2.decryption();
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
			FHE fhe2 = new FHE(args[4],args[5]);
			String cipher1 = fhe1.encryption();
			String cipher2 = fhe2.encryption();
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
			FHE fhe2 = new FHE(args[4],args[5]);
			String cipher1 = fhe1.encryption();
			String cipher2 = fhe2.encryption();
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
		else if(args.length == 4 && args[0].equals("-t")) {
			FHE fhe = new FHE(args[1],args[2],args[3]);
			boolean testResult  = fhe.equalTest(args[1], args[2]);
			if(testResult == true) {
				System.out.println("Two ciphers are equal!");
			}
			else {
				System.out.println("Two ciphers are not equal!");
			}
		}
		else if(args.length == 6 && args[0].equals("-t") && args[1].equals("-e") && args[3].equals("-e")) {
			FHE fhe1 = new FHE(args[2], args[5]);
			FHE fhe2 = new FHE(args[4],args[5]);
			String cipher1 = fhe1.encryption();
			String cipher2 = fhe2.encryption();
			FHE fhe = new FHE(cipher1,cipher2,args[5]);
			boolean testResult = fhe.equalTest(cipher1, cipher2);
			if(testResult == true) {
				System.out.println("Two ciphers are equal!");
			}
			else {
				System.out.println("Two ciphers are not equal!");
			}
		}
		else {
			System.out.println("Usage: FHEv1 -k <key size> <KeyFileName>\n");
	        System.out.println("       FHEv1 -e <m> <KeyFileName>\n");
	        System.out.println("       FHEv1 -d <Cm> <KeyFileName>\n");
	        System.out.println("       FHEv1 -b <m> <KeyFileName>\n");
	        System.out.println("       FHEV1 -a <-e <m1> | Cm1>,<-e <m2> | Cm2> <keyFileName>\n");
	        System.out.println("       FHEV1 -m <-e <m1> | Cm1>,<-e <m2> | Cm2> <keyFileName>\n");
	        System.out.println("       FHEV1 -t <-e <m1> | Cm1>,<-e <m2> | Cm2> <keyFileName>\n");
		}
	}

}
