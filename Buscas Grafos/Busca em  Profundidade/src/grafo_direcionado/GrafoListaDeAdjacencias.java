package grafo_direcionado;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;

public class GrafoListaDeAdjacencias {
    private final ArrayList<String> vertices = new ArrayList<String>();

    HashMap<Integer, LinkedList<Integer>> listaDeAdjacencias = new HashMap<Integer, LinkedList<Integer>>();

    public void addVertice(String vertice) {
        vertices.add(vertice);
        if (listaDeAdjacencias != null) {
            listaDeAdjacencias.put(getIndexVertice(vertice), new LinkedList());
        }
    }

    public void addAresta(String v1, String v2) {
        //Carrega posição dos vertices
        int posV1 = getIndexVertice(v1);
        int posV2 = getIndexVertice(v2);
        //GRAFO DIRECIONADO
        listaDeAdjacencias.get(posV1).add(posV2);
        //Se fosse grafo não direcionado
//        listaDeAdjacencias.get(posV2).add(posV1);
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

    public ArrayList<Integer> getVerticesConectados(String vertice) {
        ArrayList<Integer> verticesConectados = new ArrayList<Integer>();

        LinkedList<Integer> listaVertice = listaDeAdjacencias.get(getIndexVertice(vertice));

        verticesConectados.addAll(listaVertice);
//        System.out.println(verticesConectados);
        return verticesConectados;
    }

    public BuscaEmProfundidadeResult buscaEmProfundidade(String verticeOrigem) {

        BuscaEmProfundidadeResult auxiliar = new BuscaEmProfundidadeResult(new ArrayList<Integer>(),new ArrayList<Integer>(), new ArrayList<String>(), new ArrayList<String>(), 0);
        //Inicializa os arrays
        for (int i = 0; i < vertices.size(); i++) {
            auxiliar.descoberto.add(0);
            auxiliar.finalizado.add(0);
            auxiliar.cores.add(i, "Branco");
            auxiliar.pi.add(i, null);
        }


        for (int i = 0; i < vertices.size(); i++) {
            if(auxiliar.cores.get(i) == "Branco"){
                buscaEmProfundidadeVisita(getIndexVertice(vertices.get(i)), auxiliar);
            }
        }

        return auxiliar;

    }

    private void buscaEmProfundidadeVisita(int verticeU, BuscaEmProfundidadeResult auxiliar) {
        auxiliar.cores.set(verticeU, "Cinza");
        auxiliar.contador++;
        //System.out.println("Descoberto "+ getVerticeByIndex(verticeU) + " no tempo " + auxiliar.contador);
        auxiliar.descoberto.set(verticeU, auxiliar.contador);

        ArrayList<Integer> verticesConectados = getVerticesConectados(vertices.get(verticeU));
        for (int i = 0; i < verticesConectados.size(); i++) {
            if(auxiliar.cores.get(verticesConectados.get(i)) == "Branco"){
                auxiliar.pi.set(verticesConectados.get(i), getVerticeByIndex(verticeU));
                buscaEmProfundidadeVisita(verticesConectados.get(i),auxiliar);
            }
        }
        auxiliar.cores.set(verticeU, "Preto");
        auxiliar.contador++;
        //System.out.println("Finalizado "+ getVerticeByIndex(verticeU) + " no tempo " + auxiliar.contador);
        auxiliar.finalizado.set(verticeU, auxiliar.contador);
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
class BuscaEmProfundidadeResult {
    ArrayList<Integer> descoberto ;
    ArrayList<Integer> finalizado;
    ArrayList<String> cores;
    ArrayList<String> pi ;

    int contador;

    public BuscaEmProfundidadeResult(ArrayList<Integer> descoberto, ArrayList<Integer> finalizado, ArrayList<String> cores, ArrayList<String> pi, int contador) {
        this.descoberto = descoberto;
        this.finalizado = finalizado;
        this.cores = cores;
        this.pi = pi;
        this.contador = contador;
    }

    @Override
    public String toString() {
        return "BuscaEmProfundidadeResult{" +
                "descoberto=" + descoberto +
                ", finalizado=" + finalizado +
                ", cores=" + cores +
                ", pi=" + pi +
                ", contador=" + contador +
                '}';
    }
}
