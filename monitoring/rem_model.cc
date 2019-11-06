#include "rem_model.h"
#include <math.h>
#include <cmath>

// Add a data point to this modelParameters.and call fit model
void PredictionModel::addDataPoint(double value, double time)
{
    if (REM_DEBUG)
        cout << "New data point added to modelParameters. "
                << time << ", " << value << endl;

    this->data.push_back(value);
    this->times.push_back(time);

    // add new weighted average point
    if (this->dataCount == 0)
    {
        // add value as initial weighted average
        this->weightedAverages.push_back(value);
    }
    else
    {
        double wAvg = this->weightedAverages.at(this->dataCount - 1) * (1 - this->alpha)
        + value * this->alpha;

        this->weightedAverages.push_back(wAvg);
    }

    dataCount++;
    windowSize++;

    // check if initializing
    if (dataCount < INIT_COUNT)
    {
        if (REM_DEBUG)
            cout << "Not enough data to fit modelParameters." << endl;
        return;
    }
    else if (dataCount == INIT_COUNT)
    {
        // generate a fit
        fitModel();
        return;
    }

    // modelParameters.past initialization
    // compare this point to the expected point
    if (withinExpectedValueRange(time, value))
    {
        difCount = 0;
        this->timeToLive = DEFAULT_TTL;
        // TODO: Do we want this fitModel? What happens when a point is good?
        //fitModel();
    }
    else
    {
        // point is not within expected range
        difCount++;

        if (difCount >= MAX_DIFF_COUNT)
        {
        // too many bad data points in a row
        adaptModel(); // reset difCount
        }
        else
        {
        // check old modelParameters.to see if a mistake was made in updating the model
        compareToPreviousModel();
        }
    }
}

// calculate sigma for the given data set
void PredictionModel::calculateDeviations(vector<double> times, vector<double> values)
{
    // get sigma values
    double totalDeviation = 0;
    int n = times.size();
    // calculate deviation on current windowSize
    // TODO: Check that this is windowSize iterations
    for (int i = 0; i < n; i++)
    {
        totalDeviation += std::abs(float(values[i] - this->getDataPoint(times[i])));
    }

    // calculate sigma
    modelParameters.sigma = totalDeviation / n;

    // TODO: Add to error array?
}

 // check if the calculated value is a valid prediction
bool PredictionModel::withinExpectedValueRange(double time, double value)
{
    // if the point lies within valid value return true

    double expected = this->getDataPoint(time);
    double deviation = std::abs(float(value - expected));
    double threshold = modelParameters.sigma * NUM_DEVIATIONS;

    if (threshold < MIN_DEVIATION)
        threshold = MIN_DEVIATION;

//  cout << "Expected: " << expected << " vs. Measured: " << value << endl;
//  cout << "Error threshold: " << threshold << " vs. Deviation: " << deviation << endl;
    if ( deviation > MAX_THRESH_DIFF || value < RSS_OUT_OF_RANGE || expected < RSS_OUT_OF_RANGE)
    {
        if (REM_DEBUG)
            cout << "BAD: Threshold error" << endl;

        // zero tolerance for threshold error, make new model
        this->state = ModelState::BAD;
        difCount = MAX_DIFF_COUNT;
        return false;
    }
    else if (deviation > threshold)
    {
        if (REM_DEBUG)
            cout << "UNSTABLE: Standard deviation error" << endl;

        // standard deviation error
        this->state = ModelState::UNSTABLE;
        return false;
    }
    else if (deviation > modelParameters.sigma && ((deviation < 0 && lastDeviation < 0) || (deviation > 0 && lastDeviation > 0)))
    {
        if (REM_DEBUG)
            cout << "UNSTABLE: Bad trend error" << endl;

        // trend ERROR
        this->state = ModelState::UNSTABLE;
        return false;
    }

    this->state = ModelState::STABLE;
    return true;
}

// compare current modelParameters.to previous modelParameters. and check for mistake
// return true if old modelParameters.is better
bool PredictionModel::compareToPreviousModel()
{
  // TODO: Implement

  return false;
}

// adapt the current modelParameters.for the latest measured data in window
void PredictionModel::adaptModel()
{
    if (REM_DEBUG)
        cout << "Adapting modelParameters.to new data" << endl;

    // TODO: Consider going back to old modelParameters.
    // store current modelParameters.in old model
    this->oldModel = modelParameters;

    // build a new modelParameters.and last 'bad data'
    this->windowSize = MAX_DIFF_COUNT;

    // get data for regression
    vector<double> newData;
    vector<double> newTimes;
    vector<double> newAvgs;

    for (int i = dataCount - windowSize; i < dataCount; i++)
    {
        if (newAvgs.size() > 0)
            newAvgs.push_back(data[i - 1] * (1 - alpha) + data[i] * alpha);
        else
            newAvgs.push_back(data[i]);

        newData.push_back(data[i]);
        newTimes.push_back(times[i]);
    }

    this->performRegression(newTimes, newData, newAvgs);
    this->compareToPreviousModel();

    // create modelParameters.packet
    // broadcast packet
    modelParameters.timeToLive = DEFAULT_TTL;

    // NS3-TODO: Broadcast this message?  Simulator::Schedule(Seconds(0.00001), &BroadcastModel, this);
}

/* NS3-TODO: 
void PredictionModel::setParentNode(Ptr<Node> parent)
{
  this->parentNode = parent;
  this->ownerId = parent->GetId();
}
*/

/* Class BatteryModel */
BatteryModel::BatteryModel()
{
    this->alphaTimeout = 1.0;
    this->modelParameters.type = BATTERY;
    this->MODEL_TYPE = BATTERY;
}

void BatteryModel::initialize()
{
    if (BATTERY_DEBUG)
        cout << "Initializing battery modelParameters.for node " << this->ownerId << endl;

    // start monitoring in ns3 discrete simulator

    // NS3-TODO: Abstract battery gathering?
//    Simulator::Schedule(Seconds(this->alphaTimeout), &GatherInitialBatteryData, this);
}

double BatteryModel::getDataPoint(double time)
{
    return modelParameters.mu * time + modelParameters.beta;
}

void BatteryModel::fitModel()
{
//  if (windowSize >= INIT_COUNT)
//   cout << "Fitting battery modelParameters. << endl;

    performRegression(times, data, weightedAverages);

    modelParameters.timeToLive = DEFAULT_TTL;

    // NS3-TODO: hardware abstract???
//    Simulator::Schedule(Seconds(0.00001), &BroadcastModel, this);
}

void BatteryModel::performRegression(vector<double> times, vector<double> values, vector<double> wAvgs)
{
    // perform linear regression on data and store it in model
    double x = 0;
    double y = 0;
    double xx = 0;
    double yy = 0;
    double xy = 0;

    int n = times.size();

    for (int i = 0; i < n; i++)
    {
        x += times[i];
        y += values[i];
        xx += times[i] * times[i];
        yy += values[i] * values[i];
        xy += times[i] * values[i];
    }

    double b = (y*xx - x*xy)/(n*xx - x*x);
    double m = (n*xy - x*y)/(n*xx - x*x);

    modelParameters.mu = m;
    modelParameters.beta = b;

    if (BATTERY_DEBUG)
        cout << "New Battery modelParameters. y = " << m << "x + " << b << endl;

    this->calculateDeviations(times, values);
}

/* Class RssModel */
RssModel::RssModel()
{
    this->modelParameters.type = RSS;
    this->MODEL_TYPE = RSS;
}

void RssModel::initialize()
{
    if (RSS_DEBUG)
        cout << "Initializing local rss modelParameters.for node " << this->ownerId << " with node " << this->pairId << endl;
}

double RssModel::getDataPoint(double time)
{
    return modelParameters.mu * log(time + 10) + modelParameters.beta;
}

void RssModel::fitModel()
{
  //if (windowSize >= INIT_COUNT)
   // cout << "Fitting rss modelParameters. << endl;

    performRegression(times, data, weightedAverages);

    modelParameters.timeToLive = DEFAULT_TTL;
    // NS3-TODO: Abstarct???
//    Simulator::Schedule(Seconds(0.00001), &BroadcastModel, this);
}

void RssModel::performRegression(vector<double> times, vector<double> values, vector<double> wAvgs)
{
    // perform linear regression on data and store it in model
    double x = 0;
    double y = 0;
    double xx = 0;
    double yy = 0;
    double xy = 0;

    int n = times.size();

    for (int i = 0; i < n; i++)
    {
        // linearize input data
        double time = log(times[i] + 10);
        x += time;
        y += values[i];
        xx += time * time;
        yy += values[i]* values[i];
        xy += time * values[i];
    }

    cout << xx << endl;
    cout << yy << endl;
    cout << xy << endl;

    double b = (y*xx - x*xy)/(n*xx - x*x);
    double m = (n*xy - x*y)/(n*xx - x*x);

    modelParameters.mu = m;
    modelParameters.beta = b;

    if (RSS_DEBUG) 
        cout << "New RSS modelParameters. y = " << m << "x + " << b << endl;

    this->calculateDeviations(times, values);
}
