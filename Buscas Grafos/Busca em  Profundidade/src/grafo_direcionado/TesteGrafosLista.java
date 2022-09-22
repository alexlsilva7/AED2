package grafo_direcionado;

import java.io.IOException;
import java.util.Scanner;

public class TesteGrafosLista {
    public static void main(String[] args) {

        GrafoListaDeAdjacencias grafoListaAdjacencias = new GrafoListaDeAdjacencias();

        try {
            grafoListaAdjacencias.carregarDoArquivo("src/grafo_direcionado/entrada.txt");
        } catch (IOException e) {
            System.out.println("erro ao carregar o arquivo! "+ e.getMessage());
        }
        Scanner ler = new Scanner(System.in);
        String vertice;
        System.out.println("Busca em profundidade");
        System.out.printf("Informe o vértice de inicio para a busca:");
        vertice= ler.next();

        BuscaEmProfundidadeResult result = grafoListaAdjacencias.buscaEmProfundidade(vertice);

        System.out.println("descoberto = "+result.descoberto);
        System.out.println("finalizado = "+result.finalizado);
        System.out.println("cores = "+result.cores);
        System.out.println("pi = "+result.pi);
    }
}
