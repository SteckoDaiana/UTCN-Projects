package orderManagement.BusinessLogic;

import orderManagement.DataAccess.Querier;

public class Destroyer {
    public static <T> void run(Class<T> t, int id){
        Querier<T> q = new Querier<T>(t);
        q.delete(id);
    }
}
