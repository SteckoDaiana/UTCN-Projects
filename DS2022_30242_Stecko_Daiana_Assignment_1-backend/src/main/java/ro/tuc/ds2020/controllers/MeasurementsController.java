package ro.tuc.ds2020.controllers;


import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import ro.tuc.ds2020.dtos.ItemDetailsDTO;
import ro.tuc.ds2020.dtos.MeasurementsDetailsDTO;
import ro.tuc.ds2020.services.MeasurementsService;

import javax.validation.Valid;
import java.util.List;
import java.util.UUID;

@RestController
@CrossOrigin
@RequestMapping(value = "/measurements")
public class MeasurementsController {
    private final MeasurementsService measurementsService;

    @Autowired

    public MeasurementsController(MeasurementsService measurementsService) {
        this.measurementsService = measurementsService;
    }


    @GetMapping()
    public ResponseEntity<List<MeasurementsDetailsDTO>> getMeasurements(){
        List<MeasurementsDetailsDTO> dtos=measurementsService.findMeasurements();
        return new ResponseEntity<>(dtos, HttpStatus.OK);
    }

    @PostMapping()
    public ResponseEntity<UUID> insertMeasurements(@Valid @RequestBody MeasurementsDetailsDTO measurementsDetailsDTO){
       // System.out.println(measurementsDetailsDTO.getId()+" "+measurementsDetailsDTO.getTimestamp()+" "+measurementsDetailsDTO.getConsumption()+" "+measurementsDetailsDTO.getItemDescription());
        UUID mesID= measurementsService.insertMeasurements(measurementsDetailsDTO);
        return new ResponseEntity<>(mesID, HttpStatus.CREATED);
    }


    @GetMapping(value="/{id_mes}")
    private ResponseEntity<MeasurementsDetailsDTO> getMeasurements(@PathVariable("id_mes") UUID deviceID) {
        MeasurementsDetailsDTO dto= measurementsService.findMeasurementsbyID(deviceID);
        return new ResponseEntity<>(dto,HttpStatus.OK);
    }


    @PostMapping(value="/updateMes")
    public ResponseEntity<?> updateDevice(@Valid @RequestBody MeasurementsDetailsDTO measurementsDetailsDTO){
        return new ResponseEntity<>(measurementsService.updateDiv(measurementsDetailsDTO), HttpStatus.OK);
    }
    @DeleteMapping(value="/delete/{id_device}")
    public ResponseEntity<UUID> deleteDevice(@PathVariable("id_device") UUID deviceID){
        measurementsService.deleteDevicebyId(deviceID);
        return new ResponseEntity<>(deviceID, HttpStatus.OK);
    }




}
