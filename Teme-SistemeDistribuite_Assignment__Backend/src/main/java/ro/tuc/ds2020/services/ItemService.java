package ro.tuc.ds2020.services;

import org.springframework.stereotype.Service;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import ro.tuc.ds2020.controllers.handlers.exceptions.model.ResourceNotFoundException;
import ro.tuc.ds2020.dtos.ItemDetailsDTO;
import ro.tuc.ds2020.dtos.builders.ItemBuilder;
import ro.tuc.ds2020.entities.Item;
import ro.tuc.ds2020.entities.User;
import ro.tuc.ds2020.repositories.ItemRepository;
import ro.tuc.ds2020.repositories.UserrRepository;


import java.util.List;
import java.util.Optional;
import java.util.UUID;
import java.util.stream.Collectors;
@Service
public class ItemService {
    private static final Logger LOGGER = LoggerFactory.getLogger(ItemService.class);
    private final ItemRepository itemRepository;
    private final UserrRepository userrRepository;

    @Autowired
    public ItemService(ItemRepository itemRepository, UserrRepository userrRepository) {
        this.itemRepository = itemRepository;
        this.userrRepository = userrRepository;
    }

    public List<ItemDetailsDTO> findItems() {
        List<Item> itemList = itemRepository.findAll();
        return itemList.stream().
                map(ItemBuilder::toItemDetailsDTO).
                collect(Collectors.toList());
    }

    public ItemDetailsDTO findItemsById(UUID id_item) {
        Optional<Item> prosumerOptional = itemRepository.findById(id_item);
        if (!prosumerOptional.isPresent()) {
            LOGGER.error("Item with id {} was not found in db", id_item);
            throw new ResourceNotFoundException(Item.class.getSimpleName() + " with id: " + id_item);
        }
        return ItemBuilder.toItemDetailsDTO(prosumerOptional.get());
    }

    public UUID insertItem(ItemDetailsDTO itemDTO) {
        Optional<User> prosumerOptional=userrRepository.findByUsername(itemDTO.getUsername());

        if(!prosumerOptional.isPresent()){

            LOGGER.debug("user with username {} was inserted in db", itemDTO.getUsername());
        }
        Item item = ItemBuilder.toEntity(itemDTO);
        item.setUser(prosumerOptional.get());
        System.out.println(itemDTO.getId_item()+"  "+itemDTO.getUsername()+ " " +itemDTO.getConsumption()+ " " + itemDTO.getAdress());
        item = itemRepository.save(item);
        LOGGER.debug("Item with id {} was inserted in db", itemDTO.getId_item());


        return item.getId();
    }

    public void deleteItemsbyId(UUID id_item){
        Optional<Item> prosumerOptional = itemRepository.findById(id_item);
        if (!prosumerOptional.isPresent()) {
            LOGGER.error("Item with id {} was not found in db", id_item);
            throw new ResourceNotFoundException(Item.class.getSimpleName() + " with id: " + id_item);
        }
        itemRepository.delete(prosumerOptional.get());
    }

    public UUID updateItems(ItemDetailsDTO itemDTO) {
        Optional<Item> prosumerOptional = itemRepository.findById(itemDTO.getId_item());
        if (!prosumerOptional.isPresent()) {
            LOGGER.error("Item with id {} was not found in db", itemDTO.getId_item());
            throw new ResourceNotFoundException(Item.class.getSimpleName() + " with id: " + itemDTO.getId_item());
        }

        Item item = prosumerOptional.get();
        if(itemDTO.getAdress() !=null){
            item.setAdress(itemDTO.getAdress());
        }
        if(itemDTO.getDescription()!=null){
            item.setDescription(itemDTO.getDescription());
        }
        if(itemDTO.getConsumption()!=null){
            item.setConsumption(itemDTO.getConsumption());
        }
        itemRepository.save(item);

        return itemDTO.getId_item();
    }
}
