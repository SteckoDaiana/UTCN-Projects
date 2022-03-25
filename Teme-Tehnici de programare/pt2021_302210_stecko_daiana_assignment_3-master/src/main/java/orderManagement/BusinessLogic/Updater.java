package orderManagement.BusinessLogic;

import orderManagement.DataAccess.Querier;

public class Updater {
    public static <T> void run(Class<T> t,T c){
        Querier<T> q = new Querier<T>(t);
        q.update(c);
    }
}
