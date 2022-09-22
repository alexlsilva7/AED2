package grafo_nao_direcionado;

import java.util.ArrayList;

public class BuscaLarguraResult {
    ArrayList<Double> distancia;
    ArrayList<String> cores;
    ArrayList<String> pi;

    @Override
    public String toString() {
        return "BuscaLarguraResult{" +
                "distancia=" + distancia +
                ",cores=" + cores +
                ",pi=" + pi +
                "}";
    }

    public BuscaLarguraResult(ArrayList<Double> distancia, ArrayList<String> cores, ArrayList<String> pi) {
        this.distancia = distancia;
        this.cores = cores;
        this.pi = pi;
    }
}
