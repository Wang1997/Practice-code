package com.gizii.cld.Servlet;

import java.io.IOException;
import java.math.BigInteger;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.web.bind.ServletRequestUtils;

public class PrimeNumberServlet extends HttpServlet {
	private ArrayList<PrimeList> primeListCollection = new ArrayList<PrimeList>();
	private int maxPrimeLists = 30;

	private static final long serialVersionUID = 8777112062054531744L;

	public PrimeNumberServlet() {
		super();
	}
	
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		int numPrimes = ServletRequestUtils.getIntParameter(request, "numPrimes", 50);
		int numDigits = ServletRequestUtils.getIntParameter(request, "numDigits", 120);
		PrimeList primeList = findPrimeList(primeListCollection,numPrimes,numDigits);
		if(primeList == null){
			primeList = new PrimeList(numPrimes,numDigits,true);
			synchronized (primeListCollection) {
				if(primeListCollection.size() >= maxPrimeLists)
					primeListCollection.remove(0);
				primeListCollection.add(primeList);
			}
		}
		ArrayList<BigInteger> currentPrimes = primeList.getPrimes();
		int numCurrentPrimes = currentPrimes.size();
		int numPrimesRemaining = (numPrimes - numCurrentPrimes);
		boolean isLastResult = (numPrimesRemaining ==0);
		if(!isLastResult){
			response.setIntHeader("Refresh", 5);
		}
	}

	private PrimeList findPrimeList(ArrayList<PrimeList> primeListCollection,int numPrimes,int numDigits){
		synchronized (primeListCollection) {
			for(int i=0;i<primeListCollection.size();i++){
				PrimeList primes = (PrimeList)primeListCollection.get(i);
				if((numPrimes == primes.getNumPrimes()) && (numDigits == primes.getNumDigits()))
					return primes;
			}
			return null;
		}
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request,response);
	}

}
