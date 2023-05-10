package ro.tuc.ds2020.dtos.builders;

import ro.tuc.ds2020.dtos.MeasurementsDTO;
import ro.tuc.ds2020.dtos.MeasurementsDetailsDTO;
import ro.tuc.ds2020.entities.Measurements;

public class MeasurementsBuilder {
    public MeasurementsBuilder(){

    }
    public static MeasurementsDTO toMeasurementsDTO(Measurements measurements){
        return new MeasurementsDTO(measurements.getId(),measurements.getConsumption(),measurements.getTimestamp(),measurements.getItem().getDescription());
    }
    public static MeasurementsDetailsDTO toMeasurementsDetailsDTO(Measurements measurements){
        return new MeasurementsDetailsDTO(measurements.getId(),measurements.getConsumption(),measurements.getTimestamp(),measurements.getItem().getDescription());
    }
    public static Measurements toEntity(MeasurementsDetailsDTO measurementsDetailsDTO){
        return new Measurements(measurementsDetailsDTO.getId(),measurementsDetailsDTO.getConsumption(),measurementsDetailsDTO.getTimestamp());
    }
}
