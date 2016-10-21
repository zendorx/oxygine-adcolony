package org.oxygine.adcolony;

import android.app.Activity;
import android.content.Intent;
import android.util.Log;

import com.adcolony.sdk.AdColony;
import com.adcolony.sdk.AdColonyInterstitial;
import com.adcolony.sdk.AdColonyInterstitialListener;
import com.adcolony.sdk.AdColonyZone;

import org.oxygine.lib.extension.ActivityObserver;

public class AdcolonyAdapter extends ActivityObserver
{
    private static String TAG = "AdColonyAdapter";
    private String _zoneID;
    private AdColonyInterstitial _ad;
    private AdColonyInterstitialListener _listener;
    private Activity _activity;

    public static native void onNativeChanged(int newStatus);

    public static int ON_LOADED = 1;
    public static int ON_FAILED = 2;
    public static int ON_OPENED = 3;
    public static int ON_EXPIRED = 4;

    public AdcolonyAdapter(Activity activity, String APP_ID, String ZONE_ID)
    {
        Log.d(TAG, "AdcolonyAdapter");

        _activity = activity;
        _zoneID = ZONE_ID;
        AdColony.configure(_activity, APP_ID, ZONE_ID);


        _listener = new AdColonyInterstitialListener()
        {
            @Override
            public void onRequestFilled( AdColonyInterstitial ad )
            {
                AdcolonyAdapter.this._ad = ad;
                Log.d( TAG, "onRequestFilled" );
                onNativeChanged(ON_LOADED);
            }

            /** Ad request was not filled */
            @Override
            public void onRequestNotFilled( AdColonyZone zone )
            {
                _ad = null;
                Log.d( TAG, "onRequestNotFilled");
                onNativeChanged(ON_FAILED);
            }

            /** Ad opened, reset UI to reflect state change */
            @Override
            public void onOpened( AdColonyInterstitial ad )
            {
                _ad = null;
                Log.d(TAG, "onOpened" );
                onNativeChanged(ON_OPENED);

            }

            /** Request a new ad if ad is expiring */
            @Override
            public void onExpiring( AdColonyInterstitial ad )
            {
                _ad = null;
               // AdColony.requestInterstitial( _zoneID, _listener );
                Log.d(TAG, "onExpiring" );
                onNativeChanged(ON_EXPIRED);
            }
        };

    }

    boolean isLoaded()
    {
        return _ad != null && !_ad.isExpired();
    }

    void load()
    {
        Log.d( TAG, "Load");
        if (isLoaded())
            return;

        Log.d( TAG, "Load started");

        _ad = null;
        _activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                AdColony.requestInterstitial(_zoneID, _listener);
            }
        });

    }

    void show()
    {
        Log.d( TAG, "Show");
        
        if (!isLoaded())
            return;

        Log.d( TAG, "Show started");

        _activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                _ad.show();
                _ad = null;
            }
        });

    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {

    }

    @Override
    public void onDestroy() {
        _ad = null;
        _listener = null;
    }

    @Override
    public void onResume() {

    }

    @Override
    public void onPause() {

    }
}