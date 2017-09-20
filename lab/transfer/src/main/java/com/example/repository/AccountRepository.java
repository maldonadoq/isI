package com.example.repository;

import java.util.Collection;

import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;

import com.example.domain.Account;

public interface AccountRepository extends CrudRepository<Account, String> {

	@Query("SELECT a FROM Account a WHERE a.numero = ?1")
	Account findByNumero(String numero);

	// select a.* from account a
	@Query("SELECT a FROM Account a")
	Collection<Account> findAll();
}