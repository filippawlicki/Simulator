public class Point {
  private int x;
  private int y;

  public Point(int x, int y) {
    this.x = x;
    this.y = y;
  }

  public final int GetX() {
    return x;
  }
  public final void SetX(int x) {
    this.x = x;
  }

  public final int GetY() {
    return y;
  }
  public final void SetY(int y) {
    this.y = y;
  }
}
