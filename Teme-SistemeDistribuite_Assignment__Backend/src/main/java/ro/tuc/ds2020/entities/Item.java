package ro.tuc.ds2020.entities;

import lombok.*;
import org.hibernate.annotations.GenericGenerator;
import org.hibernate.annotations.Type;

import javax.persistence.*;
import java.util.List;
import java.util.UUID;



@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
@Builder
@Entity
@EqualsAndHashCode
@Table(name="item")
public class Item {
    @Id
    @GeneratedValue(generator = "uuid2")
    @GenericGenerator(name = "uuid2", strategy = "uuid2")
    @Type(type = "uuid-binary")
    private UUID id;

    @ManyToOne
    @JoinColumn(name = "user_id")
    private User user;

    @Column(name = "Description")
    private String description;

    @Column(name = "Adress")
    private String adress;

    @Column(name = "Maximum_consumption")
    private Integer consumption;

   @OneToMany(mappedBy = "item")
   private List<Measurements> measurements;






    public Item(UUID id_item, String description, String adress, Integer consumption) {
        this.id=id_item;
        this.description=description;
        this.adress=adress;
        this.consumption=consumption;
    }

    public Item(String description, String adress, Integer consumption) {
        this.description=description;
        this.adress=adress;
        this.consumption=consumption;

    }
}
