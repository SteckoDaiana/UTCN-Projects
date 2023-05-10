package ro.tuc.ds2020.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import ro.tuc.ds2020.entities.User;

import java.util.List;
import java.util.Optional;
import java.util.UUID;

@Repository
public interface UserrRepository extends JpaRepository<User, UUID> {

    Optional<User> findByUsername(String username);
    Optional<List<User>>findByPassword(String password);
    Optional<User>findPersonByUsernameAndPassword(String username, String password);

}
