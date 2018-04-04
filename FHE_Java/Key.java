import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.math.BigInteger;
import java.util.Random;

public class Key {
	private String keyFile;
	private int keySize;
	private int w;
	private int z;
	public Key(int keySize, String keyFile) {
		this.keySize = keySize;
		this.keyFile = keyFile;
	}
	
	public Key(int keySize, int w, int z, String keyFile) {
		this.keySize = keySize;
		this.keyFile = keyFile;
		this.w = w;
		this.z = z;
	}
	
	public void keyGen() throws IOException {
		File file = new File(keyFile);
		
		file.createNewFile();
		FileWriter fw = new FileWriter(file);
		BigInteger p1 = genPrime(keySize);
		BigInteger two = new BigInteger("2");
		BigInteger q = (p1.multiply(two)).add(BigInteger.ONE);
		
		while(!isPrime(q)){
			p1 = genPrime(keySize);
			q = (p1.multiply(two)).add(BigInteger.ONE);
		}
		
		BigInteger p2 = genPrime(keySize);
		BigInteger p3 = genPrime(keySize);
		BigInteger t = q.multiply(p3);
		BigInteger n = p1.multiply(p2);
		BigInteger h1 = new BigInteger(keySize, new Random());
		BigInteger h2 = new BigInteger(keySize, new Random());
		BigInteger expo = (p3.subtract(BigInteger.ONE)).multiply(two);
		BigInteger g1 = h1.modPow(expo, t);
		BigInteger g2 = h2.modPow(expo, t);
		
		fw.write(keySize + "\n");
		fw.write(p1 + "\n");
		fw.write(p2 + "\n");
		fw.write(p3 + "\n");
		fw.write(q + "\n");
		fw.write(g1 + "\n");
		fw.write(g2 + "\n");
		fw.write(n + "\n");
		fw.write(t + "\n");
		fw.flush();
		fw.close();
		
	}
	
	public void keyGenV2() throws IOException {
		File file = new File(keyFile);
		
		file.createNewFile();
		FileWriter fw = new FileWriter(file);
		BigInteger p1 = genPrime(keySize);
		BigInteger two = new BigInteger("2");
		BigInteger q = (p1.multiply(two)).add(BigInteger.ONE);
		
		while(!isPrime(q)){
			p1 = genPrime(keySize);
			q = (p1.multiply(two)).add(BigInteger.ONE);
		}
		
		BigInteger p2 = genPrime(keySize);
		BigInteger p3 = genPrime(keySize);
		BigInteger t = q.multiply(p3);
		BigInteger n = p1.multiply(p2);
		BigInteger h1 = new BigInteger(keySize, new Random());
		BigInteger h2 = new BigInteger(keySize, new Random());
		BigInteger expo = (p3.subtract(BigInteger.ONE)).multiply(two);
		BigInteger g1 = h1.modPow(expo, t);
		BigInteger g2 = h2.modPow(expo, t);
		
		fw.write(keySize + "\n");
		fw.write(p1 + "\n");
		fw.write(p2 + "\n");
		fw.write(p3 + "\n");
		fw.write(q + "\n");
		fw.write(g1 + "\n");
		fw.write(g2 + "\n");
		fw.write(n + "\n");
		fw.write(t + "\n");
		fw.write(w + "\n");
		fw.write(z + "\n");
		fw.flush();
		fw.close();
		
	}
	private BigInteger genPrime(int keySize) {
		
		Random rnd = new Random();
		BigInteger bg = new BigInteger(keySize, rnd);
		int certainty = 100;
		while(!bg.isProbablePrime(certainty)) {
			 rnd = new Random();
			 bg = new BigInteger(keySize, rnd);
		}
		return bg;
	}
	
	private boolean isPrime(BigInteger bg) {
		int certainty = 100;
		return bg.isProbablePrime(certainty);
	}
	
	
}
