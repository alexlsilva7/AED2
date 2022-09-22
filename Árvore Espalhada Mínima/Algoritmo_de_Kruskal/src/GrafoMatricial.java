import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;

public class GrafoMatricial {
    private final ArrayList<String> vertices = new ArrayList<String>();
    int matriz[][];


    public void addVertice(String vertice) {
        if (matriz != null) {
            vertices.add(vertice);
        }


    }

    public void addAresta(String v1, String v2, int peso) {
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
                    matriz[i][j] = peso;
                }
                if (i == posV2 && j == posV1) {
                    //System.out.println(i + " " + j);
                    matriz[i][j] = peso;
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
                if (i == posVertice && j != posVertice && matriz[i][j] != 0) {
                    verticesConectados.add(getVerticeByIndex(j));
                }
            }
        }

        return verticesConectados;
    }

    private HashMap<String, Integer> getTodasArestas() {
        //aresta = int peso
        //"AB" = 4
        HashMap<String, Integer> arestas = new HashMap<String, Integer>();
        for (int i = 0; i < (vertices.size()); i++) {
            for (int j = 0; j < (vertices.size()); j++) {
                if (matriz[i][j] != 0) {
                    int valorIJ = matriz[i][j];
                    if (i != j) {
                        if (!arestas.containsKey(getVerticeByIndex(i) + getVerticeByIndex(j))) {
                            if (!arestas.containsKey(getVerticeByIndex(j) + getVerticeByIndex(i))) {
                                arestas.put(getVerticeByIndex(i) + getVerticeByIndex(j), matriz[i][j]);
                            }
                        }
                    }

                }
            }
        }
        return arestas;
    }

    public AlgoritimoDeKruskalResult algoritimoKruskal() {
        //Conjuntos de vertices
        ArrayList<Set> conjuntosList = new ArrayList<Set>();
        for (int i = 0; i < vertices.size(); i++) {
            HashSet<String> set = new HashSet<String>();
            set.add(vertices.get(i));
            conjuntosList.add(set);
        }

        //Criar conjunto ordenado de arestas;
        HashMap<String, Integer> map = getTodasArestas();
        Object[] arrayArestas = (map.values()).toArray();
        Arrays.sort(arrayArestas);
        for (int i = 0; i < arrayArestas.length; i++) {
            int v = (int) arrayArestas[i];
            int finalI = i;
            AtomicBoolean encontrado = new AtomicBoolean(false);
            AtomicReference<String> keyRemove = new AtomicReference<String>();
            map.forEach((key, value) -> {
                if (!(encontrado.get())) {
                    if (v == value) {
                        arrayArestas[finalI] = key;
                        keyRemove.set(key);
                        encontrado.set(true);
                    }
                }
            });
            map.remove(keyRemove.get());
        }

        //Cria arvore espalhada minima
        ArrayList<String> arvore = new ArrayList<String>();
        for (int i = 0; i < arrayArestas.length; i++) {
            String aresta = (String) arrayArestas[i];
            int index1 = getIndexConjuntoVertice(conjuntosList, aresta.substring(0, 1));
            int index2 = getIndexConjuntoVertice(conjuntosList, aresta.substring(1, 2));
            if (index1 != index2) {
                arvore.add(aresta);
                //Uniao dos conjuntos
                Set conjunto1 = conjuntosList.remove(index1);
                //pega o index atualizado apos a remocao do conjunto1;
                index2 = getIndexConjuntoVertice(conjuntosList, aresta.substring(1, 2));
                Set conjunto2 = conjuntosList.remove(index2);
                HashSet novo = new HashSet();
                novo.addAll(conjunto1);
                novo.addAll(conjunto2);
                conjuntosList.add(novo);
            }
        }
        //somatorio dos pesos da arvore
        int soma_pesos = 0;
        for (String aresta: arvore) {
            soma_pesos += getPesoAresta(aresta);
        }

        return new AlgoritimoDeKruskalResult(conjuntosList, soma_pesos,arvore);
    }
    private int getPesoAresta(String aresta){
        HashMap todasArestas = getTodasArestas();
        return (int) todasArestas.get(aresta);
    }

    private int getIndexConjuntoVertice(ArrayList<Set> conjuntosList, String vertice) {
        AtomicInteger index = new AtomicInteger(-1);
        conjuntosList.forEach(v -> {
                    if (v.contains(vertice)) {
                        index.set(conjuntosList.indexOf(v));
                    }
                }
        );
        return index.get();
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
                    System.out.print("" + matriz[i][j] + "       ");
                }
                System.out.println();
            }
            System.out.println(traco);
        }

    }

    public void carregarDoArquivo(String path) throws IOException {
        BufferedReader buffRead = new BufferedReader(new FileReader(path));
        String linha = buffRead.readLine();
        ;
        String[] split_v_a = linha.split(" ");
        int quantVertices = Integer.parseInt(split_v_a[0]);
        int quantArestas = Integer.parseInt(split_v_a[1]);
        inicialiazarGrafo(quantVertices);
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
