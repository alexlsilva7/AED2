import java.io.IOException;

public class TesteGrafosMatriz {
    public static void main(String[] args) {
        GrafoMatricial grafoMatriz = new GrafoMatricial();
        try {
            grafoMatriz.carregarDoArquivo("src/entrada.txt");
        } catch (IOException e) {
            System.out.println("erro ao carregar o arquivo! " + e.getMessage());
        }
        //grafoMatriz.imprimirMatriz();
        AlgoritimoDeKruskalResult result = grafoMatriz.algoritimoKruskal();
        System.out.println(result.arvore.toString());
        System.out.println(result.pesoArvore);
    }
}
