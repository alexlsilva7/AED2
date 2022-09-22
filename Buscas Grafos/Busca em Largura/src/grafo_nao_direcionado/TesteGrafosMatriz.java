package grafo_nao_direcionado;

import java.io.IOException;
import java.util.Scanner;

public class TesteGrafosMatriz {
    public static void main(String[] args) {
        GrafoMatricial grafoMatriz = new GrafoMatricial(8);
        try {
            grafoMatriz.carregarDoArquivo("src/grafo_nao_direcionado/entrada.txt");
        } catch (IOException e) {
            System.out.println("erro ao carregar o arquivo! " + e.getMessage());
        }
        Scanner ler = new Scanner(System.in);
        String vertice;
        System.out.println("Busca em largura");
        System.out.printf("Informe o vértice de inicio para a busca:");
        vertice = ler.next();
        BuscaLarguraResult result = grafoMatriz.buscaEmLargura(vertice);

        System.out.println("distancia = " + result.distancia);
        System.out.println("cores = " + result.cores);
        System.out.println("pi = " + result.pi);
    }
}
