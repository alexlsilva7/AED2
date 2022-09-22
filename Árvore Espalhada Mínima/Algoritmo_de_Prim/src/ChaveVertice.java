public class ChaveVertice {
    String vertice;
    double chave;

    public String getVertice() {
        return vertice;
    }

    public void setVertice(String vertice) {
        this.vertice = vertice;
    }

    public double getChave() {
        return chave;
    }

    public void setChave(double chave) {
        this.chave = chave;
    }

    public ChaveVertice(String vertice, double chave) {
        this.vertice = vertice;
        this.chave = chave;
    }

    @Override
    public String toString() {
        return "CV{" +
                "v='" + vertice + '\'' +
                ", c=" + chave +
                '}';
    }
}
