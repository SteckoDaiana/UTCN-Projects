package ro.tuc.ds2020.services;

import org.springframework.stereotype.Service;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import ro.tuc.ds2020.controllers.handlers.exceptions.model.ResourceNotFoundException;
import ro.tuc.ds2020.dtos.UserDetailsDTO;
import ro.tuc.ds2020.dtos.builders.UserBuilder;
import ro.tuc.ds2020.entities.User;
import ro.tuc.ds2020.repositories.UserrRepository;


import java.util.List;
import java.util.Optional;
import java.util.UUID;
import java.util.stream.Collectors;
@Service
public class UserService {
    private static final Logger LOGGER = LoggerFactory.getLogger(UserService.class);
    private final UserrRepository userRepository;


    @Autowired
    public UserService(UserrRepository userRepository) {
        this.userRepository = userRepository;
    }

    public List<UserDetailsDTO> findPersons() {
        List<User> personList = userRepository.findAll();
        return personList.stream()
                .map(UserBuilder::toUserDetailsDTO)
                .collect(Collectors.toList());
    }

    public UserDetailsDTO findPersonById(UUID id) {
        Optional<User> prosumerOptional = userRepository.findById(id);
        if (!prosumerOptional.isPresent()) {
            LOGGER.error("Person with id {} was not found in db", id);
            throw new ResourceNotFoundException(User.class.getSimpleName() + " with id: " + id);
        }
        return UserBuilder.toUserDetailsDTO(prosumerOptional.get());
    }
    public UserDetailsDTO findPersonByUsernameAndPassword(String username, String password) {
        Optional<User> prosumerOptionalUsernamePass = userRepository.findPersonByUsernameAndPassword(username,password);

        if (!prosumerOptionalUsernamePass.isPresent()) {
            LOGGER.error("Person with this username and password {} was not found in db", username+" "+password);
            throw new ResourceNotFoundException(User.class.getSimpleName() + " with this username and password : " + username+password);
        }

        return UserBuilder.toUserDetailsDTO (prosumerOptionalUsernamePass.get());

    }

    public UUID insert(UserDetailsDTO personDTO) {
        User person = UserBuilder.toEntity(personDTO);
        person = userRepository.save(person);
        LOGGER.debug("Person with id {} was inserted in db", person.getId());
        return person.getId();
    }

    public void deletPersonById(UUID id){
        Optional<User> prosumerOptional = userRepository.findById(id);
        if (!prosumerOptional.isPresent()) {
            LOGGER.error("Person with id {} was not found in db", id);
            throw new ResourceNotFoundException(User.class.getSimpleName() + " with id: " + id);
        }

        userRepository.delete(prosumerOptional.get());
    }

    public UUID updatePerson(UserDetailsDTO personDTO) {
        Optional<User> prosumerOptional = userRepository.findById(personDTO.getId());
        if (!prosumerOptional.isPresent()) {
            LOGGER.error("Person with id {} was not found in db", personDTO.getId());
            throw new ResourceNotFoundException(User.class.getSimpleName() + " with id: " + personDTO.getId());
        }

        User user = prosumerOptional.get();
        if (personDTO.getUsername() !=null){
            user.setUsername(personDTO.getUsername());
        }
        if (personDTO.getFirstName() !=null){
            user.setFirstName(personDTO.getFirstName());
        }
        if (personDTO.getLastName() !=null){
            user.setLastName(personDTO.getLastName());
        }
        if(personDTO.getPassword()!=null){
            user.setPassword(personDTO.getPassword());
        }
        if(personDTO.getRole()!=null){
            user.setRole(personDTO.getRole());
        }
        userRepository.save(user);

        return personDTO.getId();
    }
}
