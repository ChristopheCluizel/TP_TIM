#ifndef TP4_H
#define TP4_H

#define TWO_PI 2*3.1415926535

//------------------------------------------------
// Generate Gaussian noise using Box-Muller Method
//------------------------------------------------
float AWGN_generator(float s)
{/* Generates additive white Gaussian Noise samples with zero mean and standard deviation s. */
  float temp1;
  float temp2;
  float result;
  int p;

  p = 1;
  while( p > 0 )
  {
        temp2 = ( rand() / ( (float)RAND_MAX ) );

    if ( temp2 == 0 )
    { // Compute random value again until different from zero
      p = 1;
    }
    else
    {
       p = -1;
    }
  }

  temp1 = cos( ( (float)TWO_PI ) * (rand() / ( (float)RAND_MAX )) );
  result = sqrt( -2.0 * log( temp2 )*s*s ) * temp1;

  return result;    // return the generated random sample to the caller

}
#endif // TP4_H
