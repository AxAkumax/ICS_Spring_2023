#include "stats.h"
#include <string>
#include <vector>
#include <map>
#include <cmath>

Stats::Stats(string name, const vector<int> & chain_lengths)
{
    this->name = name;
    this->chain_lengths = chain_lengths;
    this-> mean = compute_mean(chain_lengths);
    this-> stddev = compute_stddev(chain_lengths);
    this-> load_factor = mean;
    this->chains = chain_lengths.size();
    this->entries = 0;
    this-> min = 0;
    this-> max = 0;

    if (this->chain_lengths.size()>0)
    {
        this-> entries += this->chain_lengths[0];
        this->min = this->chain_lengths[0];
        this->max = this->chain_lengths[0];
        this->histogram[this->chain_lengths[0]] = 1;
        for(int i=1; i<this->chains; i++)
        {
            if(this->chain_lengths[i]< min)
            {
                min = this->chain_lengths[i];
            }
            else if (this->chain_lengths[i]> max)
            {
                max = this->chain_lengths[i];
            }
            entries += this->chain_lengths[i];
            int val = this->chain_lengths[i];
            if(!this->histogram.count(val)==0)
            {
                this->histogram[val] = 1;
            }
            else
            {
                this->histogram[val]+= 1;
            }
        }
    }
    this->span = max - min;
    //this->span = 0;
    this-> load_factor = ((double)this->entries / (double)this->chains);

}
double Stats::compute_mean(const std::vector<int> &v)
{
    //compute mean
    double sum = 0;
    for (auto &n: v)
    {
        sum+=n;
    }
    return sum / v.size();

}
double Stats::compute_stddev(const std::vector<int> &v)
{
    //computing standard deviation
    double sum_squares = 0;
    double mean = compute_mean(v);
    double len = v.size();
    for(auto &n: v)
    {
        double diff = n-mean;
        sum_squares += (diff * diff);
    }
    return std::sqrt(sum_squares / len);
}