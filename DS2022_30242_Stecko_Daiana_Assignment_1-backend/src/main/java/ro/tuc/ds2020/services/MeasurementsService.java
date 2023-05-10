package ro.tuc.ds2020.services;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import ro.tuc.ds2020.controllers.handlers.exceptions.model.ResourceNotFoundException;
import ro.tuc.ds2020.dtos.ItemDetailsDTO;
import ro.tuc.ds2020.dtos.MeasurementsDetailsDTO;
import ro.tuc.ds2020.dtos.builders.ItemBuilder;
import ro.tuc.ds2020.dtos.builders.MeasurementsBuilder;
import ro.tuc.ds2020.entities.Item;
import ro.tuc.ds2020.entities.Measurements;
import ro.tuc.ds2020.entities.User;
import ro.tuc.ds2020.repositories.ItemRepository;
import ro.tuc.ds2020.repositories.MeasurementsRepository;

import java.util.List;
import java.util.Optional;
import java.util.UUID;
import java.util.stream.Collectors;

@Service
public class MeasurementsService {
    private static final Logger LOGGER = LoggerFactory.getLogger(MeasurementsService.class);
    private final MeasurementsRepository measurementsRepository;
    private final ItemRepository itemRepository;


    @Autowired
    public MeasurementsService(MeasurementsRepository measurementsRepository, ItemRepository itemRepository) {
        this.measurementsRepository = measurementsRepository;
        this.itemRepository = itemRepository;
    }
   public List<MeasurementsDetailsDTO>findMeasurements(){
        List<Measurements> measurementsList=measurementsRepository.findAll();
        return measurementsList.stream()
                .map(MeasurementsBuilder::toMeasurementsDetailsDTO).collect(Collectors.toList());

   }
    public MeasurementsDetailsDTO findMeasurementsbyID (UUID id_device) {
        Optional<Measurements> prosumerOptional = measurementsRepository.findById(id_device);
        if (!prosumerOptional.isPresent()) {
            LOGGER.error("Device with id {} was not found in db", id_device);
            throw new ResourceNotFoundException(Item.class.getSimpleName() + " with id: " + id_device);
        }
        return MeasurementsBuilder.toMeasurementsDetailsDTO(prosumerOptional.get());
    }

    public UUID insertMeasurements(MeasurementsDetailsDTO measurementsDetailsDTO) {
        Optional<Item> prosumerOptional=itemRepository.findByDescription(measurementsDetailsDTO.getItemDescription());
        if(!prosumerOptional.isPresent()){

            LOGGER.debug("Item with description {} was inserted in db",measurementsDetailsDTO.getItemDescription());
        }
        Measurements measurements= MeasurementsBuilder.toEntity(measurementsDetailsDTO);
        measurements.setItem(prosumerOptional.get());
        measurements=measurementsRepository.save(measurements);
        LOGGER.debug("Measurement with id {} was inserted in db",measurementsDetailsDTO.getId());
        return measurements.getId();

    }


    public void deleteDevicebyId(UUID deviceID) {
        Optional<Measurements> prosumerOptional = measurementsRepository.findById(deviceID);
        if (!prosumerOptional.isPresent()) {
            LOGGER.error("Device with id {} was not found in db", deviceID);
            throw new ResourceNotFoundException(Measurements.class.getSimpleName() + " with id: " + deviceID);
        }
        measurementsRepository.delete(prosumerOptional.get());

    }

    public Object updateDiv(MeasurementsDetailsDTO measurementsDetailsDTO) {
        Optional<Measurements> prosumerOptional = measurementsRepository.findById(measurementsDetailsDTO.getId());
        if (!prosumerOptional.isPresent()) {
            LOGGER.error("Device with id {} was not found in db", measurementsDetailsDTO.getId());
            throw new ResourceNotFoundException(Item.class.getSimpleName() + " with id: " +  measurementsDetailsDTO.getId());
        }

        Measurements measurements=prosumerOptional.get();
        if(measurementsDetailsDTO.getConsumption() !=null){
            measurements.setConsumption(measurementsDetailsDTO.getConsumption());
        }
        if(measurementsDetailsDTO.getTimestamp()!=null){
            measurements.setTimestamp(measurementsDetailsDTO.getTimestamp());
        }
        if(measurementsDetailsDTO.getConsumption()!=null){
            measurements.setConsumption(measurementsDetailsDTO.getConsumption());
        }
        measurementsRepository.save(measurements);

        return measurementsDetailsDTO.getId();


    }
}
