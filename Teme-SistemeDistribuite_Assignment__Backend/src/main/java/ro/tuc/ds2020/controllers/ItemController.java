package ro.tuc.ds2020.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.hateoas.Link;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import ro.tuc.ds2020.dtos.ItemDTO;
import ro.tuc.ds2020.dtos.ItemDetailsDTO;
import ro.tuc.ds2020.services.ItemService;

import javax.validation.Valid;
import java.util.List;
import java.util.UUID;

import static org.springframework.hateoas.server.mvc.WebMvcLinkBuilder.linkTo;
import static org.springframework.hateoas.server.mvc.WebMvcLinkBuilder.methodOn;

@RestController
@CrossOrigin
@RequestMapping(value = "/device")
public class ItemController {
    private final ItemService itemService;

    @Autowired
    public ItemController(ItemService itemService){
        this.itemService=itemService;
    }

    @GetMapping()
    public ResponseEntity<List<ItemDetailsDTO>> getItems(){
        List<ItemDetailsDTO> dtos=itemService.findItems();
        return new ResponseEntity<>(dtos, HttpStatus.OK);
    }

    @PostMapping()
    public ResponseEntity<UUID> insertItem(@Valid @RequestBody ItemDetailsDTO itemDetailsDTO){
        UUID itemId= itemService.insertItem(itemDetailsDTO);
        return new ResponseEntity<>(itemId, HttpStatus.CREATED);
    }


    @GetMapping(value="/{id_item}")
    private ResponseEntity<ItemDetailsDTO> getItem(@PathVariable("id_item") UUID itemId) {
        ItemDetailsDTO dto= itemService.findItemsById(itemId);
        return new ResponseEntity<>(dto,HttpStatus.OK);
    }


    @PostMapping(value="/updateItem")
    public ResponseEntity<?> updateItems(@Valid @RequestBody ItemDetailsDTO itemDetailsDTO){
        return new ResponseEntity<>(itemService.updateItems(itemDetailsDTO), HttpStatus.OK);
    }
    @DeleteMapping(value="/delete/{id_item}")
    public ResponseEntity<UUID> deleteItem(@PathVariable("id_item") UUID itemId){
        itemService.deleteItemsbyId(itemId);
        return new ResponseEntity<>(itemId, HttpStatus.OK);
    }



}