package bot_interface;

public class GameObject {

	protected int uid;
	private float posx;
	private float posy;
	private float velx;
	private float vely;
	private float radius;
	
	GameObject(int uid) {
		this.uid = uid;
	}
	
	void update(float posx, float posy, float velx, float vely, float radius) {
		this.posx = posx;
		this.posy = posy;
		this.velx = velx;
		this.vely = vely;
		this.radius = radius;
	}

	public int getUid() {
		return uid;
	}

	public float getPosx() {
		return posx;
	}

	public float getPosy() {
		return posy;
	}

	public float getVelx() {
		return velx;
	}

	public float getVely() {
		return vely;
	}

	public float getRadius() {
		return radius;
	}
	
}
