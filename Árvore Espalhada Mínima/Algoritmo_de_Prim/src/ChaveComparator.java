import java.util.Comparator;

public class ChaveComparator implements Comparator<ChaveVertice> {
    @Override
    public int compare(ChaveVertice x, ChaveVertice y) {

        if (x.getChave() < y.getChave()) {
            return -1;
        }
        if (x.getChave() > y.getChave()) {
            return 1;
        }
        return 0;
    }
}
