package ro.tuc.ds2020.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import ro.tuc.ds2020.entities.Item;
import ro.tuc.ds2020.entities.User;

import java.util.Optional;
import java.util.UUID;

@Repository
public interface ItemRepository  extends JpaRepository<Item, UUID> {

    Optional<Item> findByDescription(String description);


}
