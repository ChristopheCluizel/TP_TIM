function [ imageQuantif ] = imquantify( image, quantification )
    quantification=quantification-1;
    ratio = 256/quantification;
    imageQuantif=round(image./ratio)/quantification;
end

