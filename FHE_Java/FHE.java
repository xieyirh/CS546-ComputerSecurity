import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.math.BigInteger;
import java.util.Random;

public class FHE {
	String bg;
	String keyFile;
	String num1;
	String num2;
	public FHE(String bg, String keyFile) {
		this.bg = bg;
		this.keyFile = keyFile;
	}
	
	public FHE(String num1, String num2, String keyFile) {
		this.num1 = num1;
		this.num2 = num2;
		this.keyFile = keyFile;
	}
	
	public String encryption() throws IOException {
		File file = new File(keyFile);
		FileReader fr = new FileReader(file);
		BufferedReader br = new BufferedReader(fr);
		int keySize = Integer.parseInt(br.readLine());
		String p1String =br.readLine(); 
		
		for(int line = 0; line < 5; line++) {
			br.readLine();
		}
		String nString = br.readLine();
		//System.out.println(p1String);
		//System.out.println(nString);
		
		br.close();
		fr.close();
		
		BigInteger p1 = new BigInteger(p1String);
		BigInteger n = new BigInteger(nString);
		
		Random rnd = new Random();
		BigInteger m = new BigInteger(bg);
		if(m.compareTo(p1) >= 0) {
			return null;
		}
		BigInteger r = new BigInteger(keySize, rnd);
		BigInteger c = ((r.multiply(p1)).add(m)).mod(n);
		
		return c.toString();
	}
	
	public String decryption() throws IOException{
		File file = new File(keyFile);
		FileReader fr = new FileReader(file);
		BufferedReader br = new BufferedReader(fr);
		int keySize = Integer.parseInt(br.readLine());
		String p1String =br.readLine(); 
		
		//System.out.println(p1String);
		
		br.close();
		fr.close();
		BigInteger p1 = new BigInteger(p1String);
		BigInteger c = new BigInteger(bg);
		BigInteger m  = c.mod(p1);
		return m.toString();
	}
	
	public String decryptionV2() throws IOException{
		File file = new File(keyFile);
		FileReader fr = new FileReader(file);
		BufferedReader br = new BufferedReader(fr);
		int keySize = Integer.parseInt(br.readLine());
		String p1String =br.readLine(); 
		//System.out.println(p1String);
		for(int line = 0; line < 7; line++) {
			br.readLine();
		}
		String wString = br.readLine();
		//System.out.println(wString);
		int w = Integer.parseInt(wString);
		br.close();
		fr.close();
		BigInteger p1 = new BigInteger(p1String);
		BigInteger c = new BigInteger(bg);
		BigInteger two = (BigInteger.ONE).shiftLeft(w);
		BigInteger m  = (c.mod(p1)).mod(two);
		return m.toString();
	}
	
	public String addition(String cipher1, String cipher2) throws NumberFormatException, IOException {
		BigInteger c1 = new BigInteger(cipher1);
		BigInteger c2 = new BigInteger(cipher2);
		File file = new File(keyFile);
		FileReader fr = new FileReader(file);
		BufferedReader br = new BufferedReader(fr);
		
		for(int line = 0; line < 7; line++) {
			br.readLine();
		}
		String nString = br.readLine();
		//System.out.println(nString);
		
		BigInteger n =new BigInteger(nString);
		
		br.close();
		fr.close();
		BigInteger add = (c1.add(c2)).mod(n);
		return add.toString();
	}
	
	public String multiplication(String cipher1, String cipher2) throws NumberFormatException, IOException {
		BigInteger c1 = new BigInteger(cipher1);
		BigInteger c2 = new BigInteger(cipher2);
		File file = new File(keyFile);
		FileReader fr = new FileReader(file);
		BufferedReader br = new BufferedReader(fr);
		
		for(int line = 0; line < 7; line++) {
			br.readLine();
		}
		String nString = br.readLine();
		//System.out.println(nString);
		
		BigInteger n =new BigInteger(nString);
		
		br.close();
		fr.close();
		BigInteger mul = (c1.multiply(c2)).mod(n);
		return mul.toString();
	}
	
	public boolean equalTest(String cipher1, String cipher2) throws IOException{
		BigInteger c1 = new BigInteger(cipher1);
		BigInteger c2 = new BigInteger(cipher2);
		BigInteger expo;
		if(c1.compareTo(c2)>= 0) {
			expo = c1.subtract(c2);
		}
		else {
			expo = c2.subtract(c1);
		}
		
		File file = new File(keyFile);
		FileReader fr = new FileReader(file);
		BufferedReader br = new BufferedReader(fr);
		for(int line = 0; line < 5; line++) {
			br.readLine();
		}
		String g1String = br.readLine();
		String g2String = br.readLine();
		//System.out.println("g1=" + g1String);
		//System.out.println("g2=" + g2String);
		br.readLine();
		String tString = br.readLine(); 
		//System.out.println("t=" + tString);
		br.close();
		fr.close();
		BigInteger g1 = new BigInteger(g1String);
		BigInteger g2 = new BigInteger(g2String);
		BigInteger t = new BigInteger(tString);
		if((g1.modPow(expo,t)).compareTo(BigInteger.ONE) == 0 && (g2.modPow(expo,t)).compareTo(BigInteger.ONE) == 0) {
			return true;
		}
		else 
			return false;
		
	}
	
	public String messagePadding(String mString) throws IOException {
		BigInteger m = new BigInteger(mString);
		
		File file = new File(keyFile);
		FileReader fr = new FileReader(file);
		BufferedReader br = new BufferedReader(fr);
		
		for(int line = 0; line < 9; line++) {
			br.readLine();
		}
		String wString = br.readLine();
		String zString = br.readLine();
		//System.out.println("w= " + wString);
		//System.out.println("z= " + zString);
		int w = Integer.parseInt(wString);
		int z = Integer.parseInt(zString);
		BigInteger two = (BigInteger.ONE).shiftLeft(w);
		if(m.compareTo(two) > 0 ) {
			br.close();
			fr.close();
			return null;
		}

		Random rnd = new Random();
		BigInteger r = new BigInteger(z, rnd);
		//System.out.println("r= " + r.toString());
		BigInteger mPadded = (r.shiftLeft(w)).add(m);
		br.close();
		fr.close();
		return mPadded.toString();
	}
}
