public class ConexaoVertice {
    int indexVertice;
    int peso;

    public ConexaoVertice(int indexVertice, int peso) {
        this.indexVertice = indexVertice;
        this.peso = peso;
    }

    @Override
    public String toString() {
        return "ConexaoVertice{" +
                "i=" + indexVertice +
                ", p=" + peso +
                '}';
    }
}
