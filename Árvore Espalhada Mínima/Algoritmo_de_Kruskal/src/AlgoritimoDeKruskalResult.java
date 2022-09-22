import java.util.ArrayList;
import java.util.Set;

public class AlgoritimoDeKruskalResult {
    ArrayList<Set> conjuntos;
    int pesoArvore;
    ArrayList<String> arvore;

    public AlgoritimoDeKruskalResult(ArrayList<Set> conjuntos, int pesoArvore, ArrayList<String> arvore) {
        this.conjuntos = conjuntos;
        this.pesoArvore = pesoArvore;
        this.arvore = arvore;
    }

    @Override
    public String toString() {
        return "AlgoritimoDeKruskalResult{" +
                "conjuntos=" + conjuntos +
                ", pesoArvore=" + pesoArvore +
                ", arvore=" + arvore +
                '}';
    }
}
