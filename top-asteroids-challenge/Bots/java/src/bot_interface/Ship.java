package bot_interface;

public class Ship extends GameObject {

	private float ang;
	private float velang;
	private float charge;
	private int score;
	
	public Ship(int uid) {
		super(uid);
	}
	
	void update(float posx, float posy, float velx, float vely, float radius, float ang, float velang, float charge, int score) {
		super.update(posx, posy, velx, vely, radius);
		this.ang = ang;
		this.velang = velang;
		this.charge = charge;
		this.score = score;
	}

	public float getAng() {
		return ang;
	}

	public float getVelang() {
		return velang;
	}

	public float getCharge() {
		return charge;
	}

	public int getScore() {
		return score;
	}
	
}
