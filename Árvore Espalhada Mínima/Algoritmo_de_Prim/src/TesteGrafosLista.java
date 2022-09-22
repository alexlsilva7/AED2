import java.io.IOException;

public class TesteGrafosLista {
    public static void main(String[] args) {

        GrafoListaDeAdjacencias grafoListaAdjacencias = new GrafoListaDeAdjacencias();

        try {
            grafoListaAdjacencias.carregarDoArquivo("src/entrada.txt");
        } catch (IOException e) {
            System.out.println("erro ao carregar o arquivo! "+ e.getMessage());
        }
        //grafoListaAdjacencias.imprimir();
        AlgoritimoPrimResult result = grafoListaAdjacencias.algoritimoPrim("a");
        System.out.println(result.pi);
        System.out.println(result.pesoArvore);
    }
}
