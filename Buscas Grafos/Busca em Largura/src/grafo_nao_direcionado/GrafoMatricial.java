package grafo_nao_direcionado;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class GrafoMatricial {
    private final ArrayList<String> vertices = new ArrayList<String>();
    int matriz[][];

    public GrafoMatricial(int quantVertices) {
        inicialiazarGrafo(quantVertices);
    }

    public void addVertice(String vertice) {
        if (matriz != null) {
            vertices.add(vertice);
        }

    }

    public void addAresta(String v1, String v2) {
        //Carrega posição dos vertices
        int posV1 = -1;
        int posV2 = -1;
        for (String vertice : vertices) {
            if (vertice.equals(v1)) {
                posV1 = vertices.indexOf(vertice);
            }
            if (vertice.equals(v2)) {
                posV2 = vertices.indexOf(vertice);
            }
        }
        //atribuição da aresta na matriz

        for (int i = 0; i < (vertices.size()); i++) {
            for (int j = 0; j < (vertices.size()); j++) {
                if (i == posV1 && j == posV2) {
                    //System.out.println(i + " " + j);
                    matriz[i][j] = 1;
                }
                if (i == posV2 && j == posV1) {
                    //System.out.println(i + " " + j);
                    matriz[i][j] = 1;
                }
            }
        }


    }


    private void inicialiazarGrafo(int quantVertices) {
        matriz = new int[quantVertices][quantVertices];

        for (int i = 0; i < quantVertices; i++) {
            for (int j = 0; j < quantVertices; j++) {
                if (i == j) {
                    matriz[i][j] = 1;
                }
            }
        }
    }

    public BuscaLarguraResult buscaEmLargura(String verticeOrigem) {
        ArrayList<Double> distancia = new ArrayList<Double>();
        ArrayList<String> cores = new ArrayList<String>();
        ArrayList<String> pi = new ArrayList<String>();

        Queue<String> fila = new LinkedList<String>();

        //Inicializa os arrays
        int posVerticeOrigem = getIndexVertice(verticeOrigem);
        for (int i = 0; i < vertices.size(); i++) {
            if (i == posVerticeOrigem) {
                distancia.add(i, Double.valueOf(0));
                cores.add(i, "Cinza");
                pi.add(i, null);
            } else {
                distancia.add(i, Double.POSITIVE_INFINITY);
                cores.add(i, "Branco");
                pi.add(i, null);
            }
        }
        //inicializa a fila com o elemento de origem
        fila.add(verticeOrigem);

        while (!fila.isEmpty()) {
            String u = fila.poll();

            ArrayList<String> verticesConectados = getVerticesConectados(u);

            verticesConectados.forEach(v -> {
                /*
                Se os elementos conectados forem brancos
                1 - Muda cor para cinza
                2 - define dustancia
                3 - define o pi como o index de u
                4 - coloca na fila o v
                 */
                if (u == "U" && v == "Y") {
                    System.out.print("");
                }
                ;
                if (cores.get(getIndexVertice(v)) == "Branco") {
                    cores.set(getIndexVertice(v), "Cinza");
                    distancia.set(getIndexVertice(v), distancia.get(getIndexVertice(u)) + 1);
                    pi.set(getIndexVertice(v), u);
                    fila.add(v);
                }
            });
            int posV = getIndexVertice(u);
            cores.set(posV, "Preto");
        }

        return new BuscaLarguraResult(distancia, cores, pi);
    }

    private int getIndexVertice(String vertice) {
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

    private ArrayList<String> getVerticesConectados(String vertice) {
        ArrayList<String> verticesConectados = new ArrayList<String>();
        int posVertice = getIndexVertice(vertice);
        for (int i = 0; i < (vertices.size()); i++) {
            for (int j = 0; j < (vertices.size()); j++) {
                if (i == posVertice && j != posVertice && matriz[i][j] == 1) {
                    verticesConectados.add(getVerticeByIndex(j));
                }
            }
        }

        return verticesConectados;
    }

    public void imprimirMatriz() {
        String traco = "";
        for (int i = 0; i < (vertices.size() * 2); i++) {
            traco = traco.concat("-");
        }
        if (vertices.isEmpty()) {
            System.out.print("matriz vazia");
        } else {
            System.out.println(traco);
            for (int i = 0; i < (vertices.size()); i++) {
                for (int j = 0; j < (vertices.size()); j++) {
                    System.out.print("" + matriz[i][j] + " ");
                }
                System.out.println();
            }
            System.out.println(traco);
        }

    }

    public void carregarDoArquivo(String path) throws IOException {
        BufferedReader buffRead = new BufferedReader(new FileReader(path));
        String linha = buffRead.readLine();;
        String[] split_v_a = linha.split(" ");
        int quantVertices = Integer.parseInt(split_v_a[0]);
        int quantArestas = Integer.parseInt(split_v_a[1]);

        for (int i = 0; i < quantVertices; i++) {
            linha = buffRead.readLine();
            addVertice(linha);
        }
        for (int i = 0; i < quantArestas; i++) {
            linha = buffRead.readLine();
            addAresta(linha.substring(0,1), linha.substring(1));
        }
        buffRead.close();
    }
}
