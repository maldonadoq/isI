package spotify.model;

import java.util.Date;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
//import javax.persistence.GeneratedValue;
//import javax.persistence.GenerationType;

@Entity
public class cancion{
	@Id
	//@GeneratedValue(strategy=GenerationType.IDENTITY)
	@Column(length = 16)
	public String Id;
	
	@Column(length = 32, nullable = false)
	public String nombre;
	
	public Date fecha;
	
	@Column(columnDefinition = "TEXT")
	public String letra;
	
	public Integer puntuacion;

	public String getId() {
		return Id;
	}

	public void setId(String id) {
		Id = id;
	}

	public String getNombre() {
		return nombre;
	}

	public void setNombre(String nombre) {
		this.nombre = nombre;
	}

	public Date getFecha() {
		return fecha;
	}

	public void setFecha(Date fecha) {
		this.fecha = fecha;
	}

	public String getLetra() {
		return letra;
	}

	public void setLetra(String letra) {
		this.letra = letra;
	}

	public Integer getPuntuacion() {
		return puntuacion;
	}

	public void setPuntuacion(Integer puntuacion) {
		this.puntuacion = puntuacion;
	}
}
