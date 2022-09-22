import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.concurrent.atomic.AtomicReference;

public class GrafoListaDeAdjacencias {
    private final ArrayList<String> vertices = new ArrayList<String>();

    HashMap<Integer, LinkedList<ConexaoVertice>> listaDeAdjacencias = new HashMap<Integer, LinkedList<ConexaoVertice>>();

    public void addVertice(String vertice) {
        vertices.add(vertice);
        if (listaDeAdjacencias != null) {
            listaDeAdjacencias.put(getIndexVertice(vertice), new LinkedList());
        }
    }

    public void addAresta(String v1, String v2, int peso) {
        //Carrega posição dos vertices
        int posV1 = getIndexVertice(v1);
        int posV2 = getIndexVertice(v2);
        listaDeAdjacencias.get(posV1).add(new ConexaoVertice(posV2, peso));
        listaDeAdjacencias.get(posV2).add(new ConexaoVertice(posV1, peso));
    }

    public ConexaoVertice getAresta(String v1, String v2) {
        LinkedList<ConexaoVertice> conexoes = listaDeAdjacencias.get(getIndexVertice(v1));
        AtomicReference<ConexaoVertice> result = new AtomicReference<ConexaoVertice>();
        conexoes.forEach(v -> {
            if (v.indexVertice == getIndexVertice(v2)) {
                result.set(v);
            }
        });
        return result.get();
    }

    public AlgoritimoPrimResult algoritimoPrim(String verticeInicial) {
        ArrayList<ChaveVertice> chaves = new ArrayList<>();
        ArrayList<String> pi = new ArrayList<>();
        int posInicial = getIndexVertice(verticeInicial);

        //Inicializa os arrays
        for (int i = 0; i < vertices.size(); i++) {
            if (i == posInicial) {
                chaves.add(new ChaveVertice(vertices.get(i), 0.0));
            } else {
                chaves.add(new ChaveVertice(vertices.get(i), Double.POSITIVE_INFINITY));
            }
            pi.add(null);
        }
        ChaveComparator verticeComparator = new ChaveComparator();
        PriorityQueue<ChaveVertice> filaPrioridade = new PriorityQueue<ChaveVertice>(vertices.size(), verticeComparator);
        filaPrioridade.addAll(chaves);
        ArrayList<ChaveVertice> removidos = new ArrayList();
        while (filaPrioridade.size() != 0) {
            ChaveVertice u = filaPrioridade.poll();
            removidos.add(u);
            ArrayList<ConexaoVertice> conexaoVertices = getVerticesConectados(u.vertice);
            for (int i = 0; i < conexaoVertices.size(); i++) {
                boolean taNaFila = filaPrioridade.contains(chaves.get(conexaoVertices.get(i).indexVertice));
                boolean pesoArestaMenorChave = getAresta(u.vertice, getVerticeByIndex(conexaoVertices.get(i).indexVertice)).peso < chaves.get((conexaoVertices.get(i)).indexVertice).chave;
                if (taNaFila && pesoArestaMenorChave) {
                    pi.set(conexaoVertices.get(i).indexVertice, u.vertice);
                    chaves.set(conexaoVertices.get(i).indexVertice, new ChaveVertice(getVerticeByIndex(conexaoVertices.get(i).indexVertice), getAresta(u.vertice, getVerticeByIndex(conexaoVertices.get(i).indexVertice)).peso));
                }
            }
            filaPrioridade.clear();
            filaPrioridade.addAll(chaves);
            filaPrioridade.removeAll(removidos);
        }
        //calcula peso total da arvore
        int somaPeso = 0;
        for (ChaveVertice c : chaves) {
            somaPeso += c.chave;
        }
        return new AlgoritimoPrimResult(chaves,somaPeso, pi);
    }

    public int getIndexVertice(String vertice) {
        for (String v : vertices) {
            if (v.equals(vertice)) {
                return vertices.indexOf(v);
            }
        }
        return -1;
    }

    private String getVerticeByIndex(int index) {
        return vertices.get(index);
    }

    public void imprimir() {
        if (vertices.isEmpty()) {
            System.out.print("lista vazia");
        } else {
            listaDeAdjacencias.forEach((key, value) -> {
                System.out.println("key: " + key + ", value: " + value.toString());
            });
        }

    }

    public ArrayList<ConexaoVertice> getVerticesConectados(String vertice) {
        ArrayList<ConexaoVertice> verticesConectados = new ArrayList<ConexaoVertice>();

        LinkedList<ConexaoVertice> listaConexaoVertice = listaDeAdjacencias.get(getIndexVertice(vertice));

        verticesConectados.addAll(listaConexaoVertice);
//        System.out.println(verticesConectados);
        return verticesConectados;
    }

    public void carregarDoArquivo(String path) throws IOException {
        BufferedReader buffRead = new BufferedReader(new FileReader(path));
        String linha = buffRead.readLine();
        ;
        String[] split_v_a = linha.split(" ");
        int quantVertices = Integer.parseInt(split_v_a[0]);
        int quantArestas = Integer.parseInt(split_v_a[1]);
        for (int i = 0; i < quantVertices; i++) {
            linha = buffRead.readLine();
            addVertice(linha);
        }
        for (int i = 0; i < quantArestas; i++) {
            linha = buffRead.readLine();
            String[] split_arestas = linha.split(" ");
            addAresta(split_arestas[0].substring(0, 1), split_arestas[0].substring(1), Integer.parseInt(split_arestas[1]));
        }
        buffRead.close();
    }


}

class AlgoritimoPrimResult {
    ArrayList<ChaveVertice> chaves;

    int pesoArvore;
    ArrayList<String> pi;

    public AlgoritimoPrimResult(ArrayList<ChaveVertice> chaves, int pesoArvore, ArrayList<String> pi) {
        this.chaves = chaves;
        this.pesoArvore = pesoArvore;
        this.pi = pi;
    }

    @Override
    public String toString() {
        return "AlgoritimoPrimResult{" +
                "chaves=" + chaves +
                ", pesoArvore=" + pesoArvore +
                ", pi=" + pi +
                '}';
    }
}
