package bot_interface;

public class Laser extends GameObject {

	private float lifetime;
	private int owner;
	
	Laser(int uid) {
		super(uid);
	}
	
	void update(float posx, float posy, float velx, float vely, float radius, float lifetime, int owner) {
		super.update(posx, posy, velx, vely, radius);
		this.lifetime = lifetime;
		this.owner = owner;
	}

	public float getLifetime() {
		return lifetime;
	}

	public int getOwner() {
		return owner;
	}	
	
}
