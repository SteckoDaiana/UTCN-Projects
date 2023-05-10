package ro.tuc.ds2020.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.hateoas.Link;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import ro.tuc.ds2020.dtos.LoginType;
import ro.tuc.ds2020.dtos.UserDTO;
import ro.tuc.ds2020.dtos.UserDetailsDTO;
import ro.tuc.ds2020.entities.User;
import ro.tuc.ds2020.repositories.UserrRepository;
import ro.tuc.ds2020.services.UserService;

import javax.validation.Valid;
import java.util.List;
import java.util.Map;
import java.util.UUID;
import java.util.*;

import static org.springframework.hateoas.server.mvc.WebMvcLinkBuilder.linkTo;
import static org.springframework.hateoas.server.mvc.WebMvcLinkBuilder.methodOn;

@RestController
@CrossOrigin
@RequestMapping(value = "/person")
public class UserController {

    private final UserService userService;

    @Autowired
    public UserController(UserService userService) {
        this.userService = userService;
    }

    @PostMapping(value="/userLogin")
    public ResponseEntity<?> userLogin(@RequestBody LoginType user) {

        UserDetailsDTO userExists = userService.findPersonByUsernameAndPassword(user.getUsername(), user.getPassword());
        return new ResponseEntity<>(userExists, HttpStatus.OK);

    }

    @GetMapping()
    public ResponseEntity<List<UserDetailsDTO>> getPersons() {
        List<UserDetailsDTO> dtos = userService.findPersons();
        for (UserDetailsDTO dto : dtos) {
            Link personLink = linkTo(methodOn(UserController.class)
                    .getPerson(dto.getId())).withRel("personDetails");
            dto.add(personLink);
        }
        return new ResponseEntity<>(dtos, HttpStatus.OK);

    }

    @PostMapping()
    public ResponseEntity<UUID> insertProsumer(@Valid @RequestBody UserDetailsDTO userDTO) {
        UUID personID = userService.insert(userDTO);
        return new ResponseEntity<>(personID, HttpStatus.CREATED);
    }

    @GetMapping(value = "/{id}")
    public ResponseEntity<UserDetailsDTO> getPerson(@PathVariable("id") UUID personId) {
        UserDetailsDTO dto = userService.findPersonById(personId);
        return new ResponseEntity<>(dto, HttpStatus.OK);
    }

    @DeleteMapping(value = "/delete/{id}")
    public ResponseEntity<UUID> deleteProsumer(@PathVariable("id") UUID personId) {
        userService.deletPersonById(personId);
        return new ResponseEntity<>(personId, HttpStatus.OK);
    }

    @PostMapping(value = "/update")
    public ResponseEntity<?> updateProsumer(@RequestBody @Valid UserDetailsDTO userDTO) {

        return new ResponseEntity<>(userService.updatePerson(userDTO), HttpStatus.OK);

    }
}